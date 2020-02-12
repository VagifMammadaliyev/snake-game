#include "area.h"


bool check_boundary(SnakeNode *node, Area *area) {
    bool in_bound_x = node->x <= area->max_cell_x && node->x >= 0;
    bool in_bound_y = node->y <= area->max_cell_y && node->y >= 0;
    return in_bound_x && in_bound_y;
}


bool check(Area *area) {
    SnakeNode *head = area->snake->head;
    SnakeNode *node = head->next;  /* skip head */

    if (!check_boundary(head, area)) return false;  /* check for head once */

    while (node) {
        if (node->x == head->x && node->y == head->y) return false;
        node = node->next;
    }
    return true;
}

/*
 * Returns boolean indicating if node added to snake
 * due to eating food.
 */
bool check_food(Area* area) {
    if (area && area->snake && area->food) {
        Food *food = area->food;
        SnakeNode *head = area->snake->head;
        if (head->x == food->x && head->y == food->y) {
            add_node(area->snake);
            delete_food(food);
            area->food = create_food(area);
            return true;
        }
    }
    return false;
}


/*
 * Creates area with snake in it.
 */
Area *create_area(Snake *snake, int max_cell_x, int max_cell_y) {
    Area *area = malloc(sizeof(*area));

    area->max_cell_y = max_cell_y;
    area->max_cell_x = max_cell_x;

    area->snake = snake;
    area->food = create_food(area);

    return area;
}


/*
 * Deletes area and snake within it.
 */
void delete_area(Area *area) {
    delete_food(area->food);
    delete_snake(area->snake);
    free(area);
}


/*
 * Creates food at random position in area.
 */
Food *create_food(Area *area) {
    Food *food = malloc(sizeof(*food));

    int new_x = 0;
    int new_y = 0;

    /* check if generated on snake */
    SnakeNode *node = NULL;
    bool on_snake = false;
    do {
        node = area->snake->head;
        new_x = rand() % area->max_cell_x;
        new_y = rand() % area->max_cell_y;
        while (node) {
            if (node->x == new_x && node->y == new_y) {
                on_snake = true;
                break;
            }
            node = node->next;
        }
    } while (on_snake);

    food->x = new_x;
    food->y = new_y;

    SDL_Rect *rect = malloc(sizeof(*rect));
    food->rect = rect;

    return food;
}


/*
 * Deletes food.
 */
void delete_food(Food *food) {
    if (food) free(food);
}


void draw_food(SDL_Renderer *renderer, Food *food) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    food->rect->h = CELL_H;
    food->rect->w = CELL_W;
    food->rect->x = food->x * CELL_H;
    food->rect->y = food->y * CELL_W;
    SDL_RenderFillRect(renderer, food->rect);
}


void draw_area(Area *area, SDL_Renderer *renderer) {
    /* draw snake */
    Snake *snake = area->snake;
    foreach_snake_node(snake, draw_node, (void*)renderer);

    /* draw food */
    if (area->food) draw_food(renderer, area->food);

    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}


void log_area(void *obj, FILE *fp) {
    Area *area = (Area*)obj;
    if (area && area->food) log_food(area->food, fp);
}

void log_food(Food *food, FILE *fp) {
    fprintf(fp, "Food: x=%d, y=%d\n", food->x, food->y);
}

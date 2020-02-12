#include "snake.h"

/*
 * Create snake node at specified positions
 * and with specified length.
 */
Snake *create_snake(int start_x, int start_y, size_t length) {
    Snake *snake = malloc(sizeof(*snake));
    size_t last_node_i = length - 1;  /* used to check for tail node */
    SnakeNode *prev_node = NULL;

    snake->size = length;
    snake->score = 0UL;

    for (size_t i = 0; i < length; i++) {
        SnakeNode *node = malloc(sizeof(*node));
        SDL_Rect *rect = malloc(sizeof(*rect));

        node->rect = rect;
        node->direction = LEFT;

        if (prev_node) {
            node->prev = prev_node;
            prev_node->next = node;
            node->next = NULL;

            node->x = prev_node->x + 1;
            node->y = prev_node->y;
        } else {  /* head node */
            node->prev = NULL;

            node->x = start_x;
            node->y = start_y;
            snake->head = node;
        }
        if (i == last_node_i) {
            snake->tail = node;
        }
        prev_node = node;
    }

    return snake;
}


/*
 * Releases memory occupied by single node.
 * This function does not releases memory for
 * next and previous nodes.
 */
void delete_node(SnakeNode *node, void *i) {
    UNUSED(i);
    if (node) {
        if (node->rect) free(node->rect);
        free(node);
    }
}


/*
 * Releases memory occupied by snake.
 */
void delete_snake(Snake *snake) {
    foreach_snake_node(snake, delete_node, NULL);
    if (snake) free(snake);
}


/*
 * Add node to snake.
 */
void add_node(Snake *snake) {
    SnakeNode *node = malloc(sizeof(*node));
    node->next = NULL;
    node->rect = malloc(sizeof(SDL_Rect));
    snake->size++;

    /* set position of a new node */
    SnakeNode *tail = snake->tail;
    switch (tail->direction) {
        case UP:
            node->y = tail->y + 1;
            node->x = tail->x;
            break;
        case DOWN:
            node->y = tail->y - 1;
            node->x = tail->x;
            break;
        case LEFT:
            node->x = tail->x + 1;
            node->y = tail->y;
            break;
        case RIGHT:
            node->x = tail->x - 1;
            node->y = tail->y;
            break;
    }

    node->direction = tail->direction;
    tail->next = node;
    node->prev = tail;
    snake->tail = node;
}


/*
 * Moves single snake node in set direction. See move_snake.
 */
void move_node(SnakeNode *node, void *ctx) {
    UNUSED(ctx);
    switch (node->direction) {
        case UP:
            node->y--;
            break;
        case DOWN:
            node->y++;
            break;
        case LEFT:
            node->x--;
            break;
        case RIGHT:
            node->x++;
            break;
    }
}


/*
 * Moves snake in set direction. See set_direction.
 */
void move_snake(Snake *snake) {
    foreach_snake_node(snake, move_node, NULL);
    foreach_snake_node_reversed(snake, update_node_direction, NULL);
}


/*
 * Updates node direction after move_snake.
 */
void update_node_direction(SnakeNode *node, void *ctx) {
    UNUSED(ctx);
    if (node->prev) {
        node->direction = node->prev->direction;
    }
}


/*
 * Sets direction for snake.
 */
void set_direction(Snake *snake, Direction new_direction) {
    if ((new_direction % 2) != (snake->head->direction % 2)) {
        snake->head->direction = new_direction;
    }
}


/*
 * Helps to iterate over nodes and apply some action on them.
 * ctx is passed to each action as parameter.
 */
inline void foreach_snake_node(Snake* snake, SnakeNodeAction action, void *ctx) {
    SnakeNode *node = snake->head;

    while (node) {
        action(node, ctx);
        node = node->next;
    }
}


/*
 * Same as foreach_snake_node but iterates in reversed order.
 */
inline void foreach_snake_node_reversed(Snake *snake, SnakeNodeAction action, void *ctx) {
    SnakeNode *node = snake->tail;

    while (node) {
        action(node, ctx);
        node = node->prev;
    }
}


/*
 * Draws single snake node and presents it.
 */
void draw_node(SnakeNode* node, void *ctx) {
    SDL_Renderer *renderer = (SDL_Renderer*)ctx;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    node->rect->w = CELL_W;
    node->rect->h = CELL_H;
    node->rect->x = node->x * CELL_W;
    node->rect->y = node->y * CELL_H;

    SDL_RenderFillRect(renderer, node->rect);
}


/*
 * Logs single snake node (for debugging purposes).
 */
void log_node(SnakeNode* node, void *ctx) {
    FILE *fp = (FILE*)ctx;
    fprintf(fp, "\tNode:\tx=%d,\ty=%d\tdir=%d\n", node->x,
                                           node->y,
                                           node->direction);
}


/*
 * Logs snake (for debugging purposes).
 */
void log_snake(void *obj, FILE *fp) {
    Snake *snake = (Snake*)obj;
    fprintf(fp, "Snake size is %lu\n", snake->size);
    foreach_snake_node(snake, log_node, (void*)fp);
}

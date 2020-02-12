#ifndef AREA_H
#define AREA_H

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "constants.h"
#include "snake.h"


typedef struct {
    int x;
    int y;
    SDL_Rect *rect;
} Food;

typedef struct {
    int cell_height;
    int cell_width;
    int max_cell_x;
    int max_cell_y;
    Snake *snake;
    Food *food;
} Area;


Area *create_area(Snake *snake, int max_cell_x, int max_cell_y);
void delete_area(Area *area);
void draw_area(Area *area, SDL_Renderer *renderer);

bool check(Area *area);
bool check_boundary(SnakeNode *node, Area *area);
bool check_food(Area* area);

Food *create_food(Area *area);
void delete_food(Food *food);

void log_area(void* area, FILE *fp);
void log_food(Food *food, FILE *fp);

#endif

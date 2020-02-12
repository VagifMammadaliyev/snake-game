#ifndef SNAKE_H
#define SNAKE_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "constants.h"
#include "utils.h"


typedef enum {
    UP=0, RIGHT=1, DOWN=2, LEFT=3
} Direction;

typedef struct SnakeNode SnakeNode;

struct SnakeNode {
    SnakeNode *next;
    SnakeNode *prev;
    int x;
    int y;
    Direction direction;
    SDL_Rect *rect;
};

typedef struct {
    SnakeNode* head;
    SnakeNode* tail;
    size_t size;
    size_t score;
} Snake;

typedef void (*SnakeNodeAction)(SnakeNode*, void*);


Snake *create_snake(size_t length);
void delete_snake(Snake *snake);
void delete_node(SnakeNode *node, void*);

void add_node(Snake *snake);
void move_node(SnakeNode *node, void*);
void move_snake(Snake *snake);
void update_node_direction(SnakeNode *node, void*);
void set_direction(Snake *snake, Direction new_direction);

void foreach_snake_node(Snake *snake, SnakeNodeAction action, void*);
void foreach_snake_node_reversed(Snake *snake, SnakeNodeAction action, void*);

void log_node(SnakeNode* node, void*);
void log_snake(void *snake, FILE* fp);

void draw_node(SnakeNode *node, void*);

#endif

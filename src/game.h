#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <SDL2/SDL.h>

#include "constants.h"
#include "snake.h"
#include "area.h"
#include "logger.h"


typedef struct {
    Area *area;
    Logger *logger;
    int speed;
    SDL_Renderer *renderer;
    SDL_Window *window;
} Game;


Game *create_game(void);
void run_game(Game *game);
void end_game(Game *game);

void log_game(void *game, FILE *fp);

#endif

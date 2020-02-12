#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "constants.h"
#include "snake.h"
#include "area.h"


void log_state(Area *area) {
    static FILE *fp = NULL;
    if (!fp) {
        char *log_file_path = getenv("SNAKE_LOG_FILE");
        fp = fopen(log_file_path, "a");
        fputs("\nSESSION\n-------\n", fp);
    }
    if (area->snake) log_snake(area->snake, fp);
    if (area->food) log_food(area->food, fp);
}


int main(void) {
    srand(time(NULL));
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Can't initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Snake Game",
                                           WIN_X, WIN_Y,
                                           WIN_W, WIN_H,
                                           SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
                                                SDL_RENDERER_PRESENTVSYNC);

    Snake *snake = create_snake(MAX_CELL_X / 2, MAX_CELL_Y / 2, START_SIZE);
    Area *area = create_area(snake, MAX_CELL_X, MAX_CELL_Y);

    /* game loop */
    int delay = 1000 / SPEED;
    SDL_Event event;
    bool running = true;
    while (running) {
        /* perform logging */
        log_state(area);

        SDL_Delay(delay);
        if (!check(area)) {
            delete_area(area);
            snake = create_snake(MAX_CELL_X / 2, MAX_CELL_Y / 2, START_SIZE);
            area = create_area(snake, MAX_CELL_X, MAX_CELL_Y);
        }
        draw_area(area, renderer);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        set_direction(snake, UP);
                        break;
                    case SDLK_DOWN:
                        set_direction(snake, DOWN);
                        break;
                    case SDLK_LEFT:
                        set_direction(snake, LEFT);
                        break;
                    case SDLK_RIGHT:
                        set_direction(snake, RIGHT);
                        break;
                }
                break;
            }
        }
        move_snake(snake);
        check_food(area);
    }

    if (area) delete_area(area);
    SDL_Quit();
}
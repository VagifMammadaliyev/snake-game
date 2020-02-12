#include "game.h"


static bool game_created = false;

/*
 * Creates area with snake in it.
 * Creates logger and counts player score.
 * This function is also responsible for SDL related things.
 */
Game *create_game(void) {
    if (game_created) return NULL;

    srand(time(NULL));

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Snake Game", WIN_X, WIN_Y, WIN_W, WIN_H, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    Snake *snake = create_snake(START_SIZE);
    Area *area = create_area(snake, MAX_CELL_X, MAX_CELL_Y);
    Game *game = malloc(sizeof(*game));

    if (!(area || snake || game)) return NULL;

    game->speed = SPEED;
    game->area = area;
    game->logger = init_logger();
    game->renderer = renderer;
    game->window = window;

    game_created = true;

    add_logfunc(game->logger, log_snake, (void*)snake);
    add_logfunc(game->logger, log_area, (void*)area);
    add_logfunc(game->logger, log_game, (void*)game);

    return game;
}


/*
 * Runs main game loop.
 */
void run_game(Game *game) {
    if (!game) return;
    if (!game->area) return;
    if (!game->area->snake) return;

    SDL_Event *event = malloc(sizeof(*event));
    if (!event) return;

    Direction direction;
    Area *area;
    Snake *snake;
    bool running;

    area = game->area;
    snake = area->snake;
    running = true;

    while (running) {
        if (SDL_PollEvent(event)) {
            if (event->type == SDL_QUIT) {
                running = false;
            }

            if (event->type == SDL_KEYDOWN) {
                switch (event->key.keysym.sym) {
                    case SDLK_UP:
                        direction = UP;
                        break;
                    case SDLK_DOWN:
                        direction = DOWN;
                        break;
                    case SDLK_LEFT:
                        direction = LEFT;
                        break;
                    case SDLK_RIGHT:
                        direction = RIGHT;
                        break;
                }
                set_direction(snake, direction);
            }
        }

        move_snake(snake);
        if (!check(area)) break;  /* snake hits wall or itself */
        if (check_food(game->area)) {
            snake->score++;
            if (snake->size % ADD_SPEED_AFTER == 0) {
                game->speed += 1;
            }
        }

        perform_log(game->logger);
        draw_area(area, game->renderer);
        SDL_Delay(1000 / game->speed);
    }
}


/*
 * Frees everything related to game.
 */
void end_game(Game *game) {
    if (game) {
        printf("Your score was: %lu\n", game->area->snake->score);
        delete_area(game->area);
        deinit_logger(game->logger);
        SDL_DestroyWindow(game->window);
        free(game);
    }
    SDL_Quit();
}


void log_game(void *obj, FILE *fp) {
    Game *game = (Game*)obj;
    if (game) {
        fprintf(fp, "Game: speed=%d, score=%lu\n", game->speed, game->area->snake->score);
    }
}

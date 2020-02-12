#include <stdio.h>
#include "game.h"


int main(void) {
    Game *game = create_game();
    run_game(game); end_game(game);
    return 0;
}

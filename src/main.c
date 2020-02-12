#include <stdio.h>
#include "game.h"


int main(void) {
    Game *game = create_game();
    if (game) { run_game(game); end_game(game); }
    else { printf("Can't start game.\n"); }
    return 0;
}

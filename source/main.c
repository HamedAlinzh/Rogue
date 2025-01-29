#include "rogue.h"

void render(Game *game){
    drawlevel(game->levels[game->clevel - 1]);
    gamehub(game->levels[game->clevel - 1]);
    move(game->levels[game->clevel - 1]->user->pos->y, game->levels[game->clevel - 1]->user->pos->x);
}

int start(Game *game){
    srand(time(0));
    Position *newposition;
    Level *level;
    setupscreen();
    if (game->clevel == 0){
        game->levels[game->clevel] = createlevel(1);
        game->clevel++;
    }
    level = game->levels[game->clevel - 1];
    // level = createlevel(1);
    gamehub(level);
    // move(level->user->pos->y, level->user->pos->x);
    // refresh();
    int ch = '\0';
    while (ch != 27){
        movemonster(level);
        newposition = handle_input(ch, level->user);
        checkposition(newposition, level);
        // clear();
        // drawlevel(level);
        // gamehub(level);
        render(game);
        move(game->levels[game->clevel - 1]->user->pos->y, game->levels[game->clevel - 1]->user->pos->x);
        ch = getch();
    }
    endwin();
    return 0;
}
// int main(){
//     start();
// }

#include "rogue.h"

int start(){
    // srand(time(0));
    Position *newposition;
    Level *level;
    setupscreen();
    level = createlevel(1);
    gamehub(level);
    // mvprintw(1, 1, "HELLO!");
    move(level->user->pos->y, level->user->pos->x);
    // move(newposition->y, newposition->x);
    // refresh();
    int ch;
    while ((ch = getch()) != 27){
        gamehub(level);
        newposition = handle_input(ch, level->user);
        checkposition(newposition, level);
        movemonster(level);
        move(level->user->pos->y,level->user->pos->x);
    }
    endwin();
    return 0;
}

#include "rogue.h"


int setupscreen(){
    initscr();
    start_color();
    init_pair(0xFF, COLOR_BLACK, COLOR_WHITE);
    bkgd(COLOR_BLACK);
    refresh();
    noecho();
    return 1;
}

int gamehub(Level *level){
    mvprintw(46, 5, "LEVEL: %d", level->level);
    mvprintw(46, 15,"GOLD: %d", level->user->gold);
    mvprintw(46, 25, "XP: %d", level->user->xp);
    mvprintw(46, 35,"HP: %d     ", level->user->health);
}
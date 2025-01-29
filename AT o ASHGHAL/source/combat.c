#include <rogue.h>


int combat(playerG* player, Monster* monster, int ord){
    if (ord == 1){
        monster->health -= player->attack;
        if (monster->health > 0){
            player->health -= monster->attack;
        }
        else {
            mvprintw(monster->pos->y, monster->pos->x, ".");
            player->xp += 1;
        }
    }
    else {
        player->health -= monster->attack;
        if (player->health > 0){
            monster->health -= player->attack;
        }
        else 
            mvprintw(1, 1,"%d", player->health);
    }
    return 1;
}
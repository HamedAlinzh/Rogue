#include "rogue.h"
playerG *playersetup(){
    playerG *newplayer;
    newplayer = (playerG*)malloc(sizeof(playerG));
    newplayer->pos = malloc(sizeof(Position));
    newplayer->gold = 0;
    newplayer->xp = 0;
    newplayer->maxhealth = 20;
    newplayer->health = 20;
    newplayer->attack = 1; //!!!! selah

    return newplayer;
}

Position* handle_input(int ch, playerG *user){
    Position *newPosition = malloc(sizeof(Position));
    switch (ch){
            //up
        case 'W':
        case 'w':
        case '8':
            newPosition->y = user->pos->y - 1;
            newPosition->x = user->pos->x;
            break;
            //left
        case 'A':
        case 'a':
        case '4':
            newPosition->y = user->pos->y;
            newPosition->x = user->pos->x - 1;
            break;
            //down
        case 'S':
        case 's':
        case '2':
            newPosition->y = user->pos->y + 1;
            newPosition->x = user->pos->x;
            break;
            //right
        case 'D':
        case 'd':
        case '6':
            newPosition->y = user->pos->y;
            newPosition->x = user->pos->x + 1;
            break;
        case '7':
            newPosition->y = user->pos->y - 1;
            newPosition->x = user->pos->x - 1;
            break;
        case '9':
            newPosition->y = user->pos->y - 1;
            newPosition->x = user->pos->x + 1;
            break;
        case '1':
            newPosition->y = user->pos->y + 1;
            newPosition->x = user->pos->x - 1;
            break;
        case '3':
            newPosition->y = user->pos->y + 1;
            newPosition->x = user->pos->x + 1;
            break;
    }
    return newPosition;
}

int playermove(Position *newpos, playerG *user, char **level){
    char buffer[2];
    sprintf(buffer, "%c", level[user->pos->y][user->pos->x]);
    // if (mvinch(user->pos.y, user->pos.x) == '.' || mvinch(y, x) == '.'){
    mvprintw(user->pos->y, user->pos->x, "%s", buffer);
    user->pos->y = newpos->y;
    user->pos->x = newpos->x;
    mvprintw(user->pos->y, user->pos->x, "@");
    move(user->pos->y, user->pos->x);
//     }
//     else if (mvinch(user->pos.y, user->pos.x) == '+'){
//         mvprintw(user->pos.y, user->pos.x, "+");
//         user->pos.y = y;
//         user->pos.x = x;
//         mvprintw(user->pos.y, user->pos.x, "@");
//         move(user->pos.y, user->pos.x);
//     }
//     else if (mvinch(user->pos.y, user->pos.x) == '#'){
//         mvprintw(user->pos.y, user->pos.x, "#");
//         user->pos.y = y;
//         user->pos.x = x;
//         mvprintw(user->pos.y, user->pos.x, "@");
//         move(user->pos.y, user->pos.x);
//     }
}
int checkposition(Position *newposition, Level *level){
    playerG* user;
    user = level->user;
    switch(mvinch(newposition->y, newposition->x)){
        case '.':
        case '+':
        case '#':
            playermove(newposition, user, level->tiles);
            break;
        case 'S':
        case 'G':
        case 'T':
            combat(user, findmonst(newposition, level->monsters), 1);
        default:
            move(user->pos->y, user->pos->x);
            break;
    }
}

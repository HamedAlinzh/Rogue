#include "rogue.h"

/*

Spider
    symbol: S
    levels 1-3
    health: 2
    attack: 1
    speed: 1
    defence: 1
    pathfinding: 1 (random)

Goblin
    symbol: G
    levels 1-5
    health: 5
    attack: 3
    speed: 1
    defence: 1
    pathfinding: 2 (seeking)


Troll
    Symbol: T
    levels 1-3
    health: 15
    attack: 5
    speed: 1
    defence: 1
    pathfinding: 1 (random)

*/
int addmonsters(Level *level){
    level->monsters = malloc(sizeof(Monster *) * 6);
    level->monsternum = 0;
    for (int x = 0; x < level->roomnum; x++){
        if ((rand() % 2) == 0){
            level->monsters[level->monsternum] = selectMonster(level->level);
            SetStartPos(level->monsters[level->monsternum], level->rooms[x]);
            level->monsternum++;
        }
    }
}


Monster *selectMonster(int level){
    int monster;
    switch (level){
        case 1:
        case 2:
        case 3:
            monster = rand() % 2 + 1;
            break;
        case 4:
        case 5:
            monster = rand() % 2 + 1;
            break;
        case 6:
            monster = 3;
            break;
    }
    switch (monster)
    {
        case 1:
            return createmonster('S', 2, 1, 1, 1, 1);
        
        case 2:
            return createmonster('G', 5, 3, 1, 1, 2);
        
        case 3:
            return createmonster('T', 10, 5, 1, 1, 1);
    }
}

Monster *createmonster(char symbol, int health, int attack, int speed, int defence, int pathfinding){
    Monster *nmonster;
    nmonster = malloc(sizeof(Monster));
    nmonster->symbol = symbol;
    nmonster->health = health;
    nmonster->attack = attack;
    nmonster->speed = speed;
    nmonster->defence = defence;

    sprintf(nmonster->buff, "%c", symbol);

    nmonster->pathfinding = pathfinding;

    return nmonster;
}

int SetStartPos(Monster *monster, Room *room){
    monster->pos = malloc(sizeof(Position));
    monster->pos->y = (rand() % (room->height - 2)) + room->pos.y + 1;
    monster->pos->x = (rand() % (room->width - 2)) + room->pos.x + 1;
    mvprintw(monster->pos->y, monster->pos->x, "%s", monster->buff); //!asdsa
}

int movemonster(Level *level){
    for (int x = 0; x < level->monsternum; x++){
        if (level->monsters[x]->health <= 0){
            continue;
        }
        mvprintw(level->monsters[x]->pos->y, level->monsters[x]->pos->x, ".");
        if (level->monsters[x]->pathfinding == 1){// random
            pathrand(level->monsters[x]->pos);
        } 
        else {
            pathfinding(level->monsters[x]->pos, level->user->pos);
        }
        mvprintw(level->monsters[x]->pos->y, level->monsters[x]->pos->x, "%s", level->monsters[x]->buff);
    }
}

int pathfinding(Position *start, Position *end){
        /* step left */
    if ((abs((start->x - 1) - end->x) < abs(start->x - end->x)) && (mvinch(start->y, start->x - 1) == '.'))
    {
        start->x = start->x - 1;

    /* step right */
    } else if ((abs((start->x + 1) - end->x) < abs(start->x - end->x)) && (mvinch(start->y, start->x + 1) == '.'))
    {
        start->x = start->x + 1;
    
    /* step down */
    } else if ((abs((start->y + 1) - end->y) < abs(start->y - end->y)) && (mvinch(start->y + 1, start->x) == '.'))
    {
        start->y = start->y + 1;

    /* step up */
    } else if ((abs((start->y - 1) - end->y) < abs(start->y - end->y)) && (mvinch(start->y - 1, start->x) == '.'))
    {
        start->y = start->y - 1;
    }
    else {

    }

    return 1;
}

int pathrand(Position *pos){
    int random = rand() % 5;
    switch (random)
    {
        //up
        case 0:
            if (mvinch(pos->y - 1, pos->x) == '.'){
                pos->y = pos->y - 1;
            }
            break;
            //down
        case 1:
            if (mvinch(pos->y + 1, pos->x) == '.'){
                pos->y = pos->y + 1;
            }
            break;
            //funk you up
        case 2:
            if (mvinch(pos->y, pos->x - 1) == '.'){
                pos->x = pos->x - 1;
            }
            break;
            //right
        case 3:
            if (mvinch(pos->y, pos->x + 1) == '.'){
                pos->x = pos->x + 1;
            }
            break;
            //nothing
        case 4:
            break;
    }
    return 1;
}

Monster* findmonst(Position* pos, Monster** monsters){
    for( int i = 0; i < 6; i++){
        if (pos->y == monsters[i]->pos->y && pos->x == monsters[i]->pos->x){
            return monsters[i];
        }
    }
    return NULL;
}
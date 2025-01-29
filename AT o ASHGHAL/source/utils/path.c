#include "rogue.h"
#include "utils.h"

void path(Position *s, Position *e){
    int x, y;
    int **frontier = malloc(190 * 49 * sizeof(int*));
    int ***comefrom = malloc(sizeof(int **) * 49);
    int frontiercount = 0;
    int frontierindex = 0;
    for (int i = 0; i < 190 * 49; i++){
        frontier[i] = malloc(sizeof(int) * 2);
    }
    for (int i = 0; i < 49; i++){
        comefrom[i] = malloc(sizeof(int *) * 49);
        for (int j = 0; j < 190; j++){
            comefrom[i][j] = malloc(sizeof(int) * 2);
            comefrom[i][j][0] = -1;
            comefrom[i][j][1] = -1;
        }
    }

    comefrom[s->y][s->x][0] = -2;
    comefrom[s->y][s->x][1] = -2;

    addposYX(frontier, s->y, s->x, frontiercount);
    frontiercount++;

    while(frontierindex < frontiercount){
        y = frontier[frontierindex][0];
        x = frontier[frontierindex][1];
        frontierindex++;
        if (y == e->y && x == e->x)
            break;
        frontiercount = addnearby(frontier, comefrom, frontiercount, y, x);
    }
    y = e->y;
    x = e->x;

    while (y != s->y || x != s->x){
        y = comefrom[y][x][0];
        x = comefrom[y][x][1];
        mvprintw(y, x, "#");
        getch();
    }
}

void addposYX(int **frontier, int y, int x, int count){
    frontier[count][0] = y;
    frontier[count][1] = x;
}
int addnearby(int **frontier, int ***comefrom, int count, int y, int x){
    if (y > 0 && comefrom[y - 1][x][0] < 0){
        addposYX(frontier, y - 1, x, count);
        count++;
        comefrom[y-1][x][0] = y;
        comefrom[y-1][x][1] = x;
    }
    if (y < 48 && comefrom[y + 1][x][0] < 0){
        addposYX(frontier, y - 1, x, count);
        count++;
        comefrom[y+1][x][0] = y;
        comefrom[y+1][x][1] = x;
    }
    if (x > 0 && comefrom[y][x - 1][0] < 0){
        addposYX(frontier, y - 1, x, count);
        count++;
        comefrom[y][x-1][0] = y;
        comefrom[y][x-1][1] = x;
    }
    if (x < 189 && comefrom[y][x + 1][0] < 0){
        addposYX(frontier, y - 1, x, count);
        count++;
        comefrom[y][x + 1][0] = y;
        comefrom[y][x + 1][1] = x;
    }
    return count;
}
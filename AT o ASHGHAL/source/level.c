#include "rogue.h"
Level *createlevel(int level){
    Level *newlevel;
    newlevel = malloc(sizeof(Level));
    newlevel->level = level;
    newlevel->roomnum = 6;
    newlevel->rooms = roomsetup();
    newlevel->tiles = savelevel();
    newlevel->user = playersetup();
    newlevel->user->pos->y = newlevel->rooms[0]->pos.y + 2;
    newlevel->user->pos->x = newlevel->rooms[0]->pos.x + 2;
    mvprintw(newlevel->user->pos->y, newlevel->user->pos->x, "@");
    move(newlevel->user->pos->y, newlevel->user->pos->x);
    addmonsters(newlevel);
    return newlevel;
}

Room** roomsetup() {
    Room **rooms;
    rooms = malloc(sizeof(Room) * 6);

    int starty[6];
    int startx[6];
    int heights[6];
    int widths[6];
    for (int i = 0; i < 3; i++){
        starty[2 * i] = rand() % 10 + 1;
        startx[2 * i] = rand() % 25 + 2 + (60 * i);
        heights[2 * i] = rand() % 8 + 6;
        widths[2 * i] = rand() % 30 + 6;
    }
    for (int i = 0; i < 3; i++){
        starty[2 * i + 1] = rand() % 12 + 1 + 24;
        startx[2 * i + 1] = rand() % 30 + 2 + (60 * i);
        heights[2 * i + 1] = rand() % 6 + 6;
        widths[2 * i + 1] = rand() % 20 + 6;
    }

    rooms[0] = createRoom(starty[0], startx[0], heights[0], widths[0]);
    drawroom(rooms[0]);
    rooms[1] = createRoom(starty[1], startx[1], heights[1], widths[1]);
    drawroom(rooms[1]);
    rooms[2] = createRoom(starty[2], startx[2], heights[2], widths[2]);
    drawroom(rooms[2]);
    rooms[3] = createRoom(starty[3], startx[3], heights[3], widths[3]);
    drawroom(rooms[3]);
    rooms[4] = createRoom(starty[4], startx[4], heights[4], widths[4]);
    drawroom(rooms[4]);
    rooms[5] = createRoom(starty[5], startx[5], heights[5], widths[5]);
    drawroom(rooms[5]);

    // connectDoors(rooms[0]->door[3], rooms[2]->door[1]);
    pathFind(rooms[0]->door[3], rooms[2]->door[1]);
    pathFind(rooms[0]->door[2], rooms[1]->door[0]);
    pathFind(rooms[2]->door[2], rooms[3]->door[0]);
    pathFind(rooms[1]->door[3], rooms[3]->door[1]);
    pathFind(rooms[3]->door[3], rooms[5]->door[1]);
    pathFind(rooms[4]->door[2], rooms[5]->door[0]);
    pathFind(rooms[2]->door[3], rooms[4]->door[1]);
    pathFind(rooms[0]->door[0], rooms[2]->door[0]);
    // connectDoors(rooms[0]->door[2], rooms[1]->door[0]);

    return rooms;
}

char ** savelevel(){
    int x, y;
    char ** positions;
    positions = malloc(sizeof(char*) * 49);
    for (y = 0; y < 49; y++){
        positions[y] = malloc(sizeof(char) * 190);
        for (x = 0; x < 190; x++){
            positions[y][x] = mvinch(y, x);
        }
    }

    return positions;
}
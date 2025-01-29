#include "rogue.h"
Room* createRoom(int y, int x, int height, int width){
    Room *nroom;
    nroom = malloc(sizeof(Room));
    nroom->pos.y = y;
    nroom->pos.x = x;
    nroom->height = height;
    nroom->width = width;
    nroom->door = malloc(sizeof(Position) * 4);
    // left door
    nroom->door[1] = (Position*)malloc(sizeof(Position));
    nroom->door[1]->y = rand() % (height - 2) + nroom->pos.y + 1;
    nroom->door[1]->x = nroom->pos.x;
    //right door
    nroom->door[3] = (Position*)malloc(sizeof(Position));
    nroom->door[3]->y = rand() % (height - 2) + nroom->pos.y + 1;
    nroom->door[3]->x = nroom->pos.x + nroom->width - 1;
    // top door
    nroom->door[0] = (Position*)malloc(sizeof(Position));
    nroom->door[0]->y = nroom->pos.y;
    nroom->door[0]->x = rand() % (width - 2) + nroom->pos.x + 1;
    // bottom door
    nroom->door[2] = (Position*)malloc(sizeof(Position));
    nroom->door[2]->y = nroom->height + nroom->pos.y - 1;
    nroom->door[2]->x = rand() % (width - 2) + nroom->pos.x + 1;

    return nroom;
}

int connectDoors(Position * doorOne, Position * doorTwo)
{
    Position temp;
    Position previous;

    int count = 0;

    temp.x = doorOne->x;
    temp.y = doorOne->y;

    previous = temp;

    while (1)
    {
        /* step left */
        if ((abs((temp.x - 1) - doorTwo->x) < abs(temp.x - doorTwo->x)) && (mvinch(temp.y, temp.x - 1) == ' '))
        {
            previous.x = temp.x;
            temp.x = temp.x - 1;

        /* step right */
        } else if ((abs((temp.x + 1) - doorTwo->x) < abs(temp.x - doorTwo->x)) && (mvinch(temp.y, temp.x + 1) == ' '))
        {
            previous.x = temp.x;
            temp.x = temp.x + 1;
        
        /* step down */
        } else if ((abs((temp.y + 1) - doorTwo->y) < abs(temp.y - doorTwo->y)) && (mvinch(temp.y + 1, temp.x) == ' '))
        {
            previous.y = temp.y;
            temp.y = temp.y + 1;

        /* step up */
        } else if ((abs((temp.y - 1) - doorTwo->y) < abs(temp.y - doorTwo->y)) && (mvinch(temp.y - 1, temp.x) == ' '))
        {
            previous.y = temp.y;
            temp.y = temp.y - 1;
        } else
        {
            if (count == 0)
            {
                temp = previous;
                count++;
                continue;
            }
            else
            {
                return 0;
            }
        }

        mvprintw(temp.y, temp.x, "#");

    }

    return 1;
}
int drawroom(Room *room) {
    // Draw top and bottom walls
    for (int x = room->pos.x; x < room->pos.x + room->width; x++) {
        mvprintw(room->pos.y, x, "-");  // Top wall
        mvprintw(room->pos.y + room->height - 1, x, "-");  // Bottom wall
    }

    // Draw left and right walls
    for (int y = room->pos.y + 1; y < room->pos.y + room->height - 1; y++) {
        mvprintw(y, room->pos.x, "|");  // Left wall
        mvprintw(y, room->pos.x + room->width - 1, "|");  // Right wall
    }

    // Fill the inside of the room with dots
    for (int y = room->pos.y + 1; y < room->pos.y + room->height - 1; y++) {
        for (int x = room->pos.x + 1; x < room->pos.x + room->width - 1; x++) {
            mvprintw(y, x, ".");  // Fill with dots
        }
    }
    // doors
    for (int i = 0; i < 4; i++){
        mvprintw(room->door[i]->y, room->door[i]->x, "+");
    }
    // pillars
    room->pillar[0].x = rand() % (room->width - 4) + room->pos.x + 2;
    room->pillar[0].y = rand() % (room->height - 4) + room->pos.y + 2;
    room->pillar[1].x = rand() % (room->width - 4) + room->pos.x + 2;
    room->pillar[1].y = rand() % (room->height - 4) + room->pos.y + 2;
    room->pillar[2].x = rand() % (room->width - 4) + room->pos.x + 2;
    room->pillar[2].y = rand() % (room->height - 4) + room->pos.y + 2;
    for (int i = 0; i < rand() % 3; i++){
        mvprintw(room->pillar[i].y, room->pillar[i].x, "O");
    }
    return 1;
}



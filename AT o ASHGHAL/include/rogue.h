#ifndef ROGUE_H
#define ROGUE_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#define MAX_HEIGHT 49
#define MAX_WIDTH 190

typedef struct Position{
    int x;
    int y;
} Position;

typedef struct {
    int y, x;
} QueueNode;

typedef struct Level
{
    char **tiles;
    int level;
    struct Room ** rooms;
    int roomnum;
    struct Monster **monsters;
    int monsternum;
    struct playerG *user;
} Level;

typedef struct Monster{
    char buff[2];
    char symbol;
    int health;
    int attack;
    int speed;
    int defence;
    Position *pos;
    int pathfinding;

} Monster;

typedef struct playerG{
    
    Position *pos;
    int health;
    int attack;
    int gold;
    int maxhealth;
    int xp;
    struct Room *room;
} playerG;

typedef struct Room{
    Position pos;
    int height;
    int width;
    Position pillar[3];
    Position **door;
}Room;
int start();
playerG *playersetup();
int setupscreen();
Position* handle_input(int ch, playerG*user);
int playermove(Position *newpos, playerG *user, char **level);
int checkposition(Position *newposition, Level* level);
Room** roomsetup();
// Room functions
Room* createRoom(int y, int x, int height, int width);
int drawroom(Room *room);
int connectDoors(Position * doorOne, Position * doorTwo);
char ** savelevel();
Level *createlevel(int level);

int addmonsters(Level *level);
Monster *selectMonster(int level);
Monster *createmonster(char symbol, int health, int attack, int speed, int defence, int pathfinding);
int SetStartPos(Monster *monster, Room *room);
int movemonster(Level *level);
int pathfinding(Position *start, Position *end);
int pathrand(Position *pos);
Monster* findmonst(Position* pos, Monster** monsters);
int gamehub(Level *level);

int combat(playerG* player, Monster* monster, int ord);

void pathFind(Position *start, Position *end);
void shuffleDirections(int directions[4][2]);
#endif
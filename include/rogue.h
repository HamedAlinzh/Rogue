#ifndef ROGUE_H
#define ROGUE_H

#include<stdio.h>
#include<ncurses.h>
#include<string.h>
#include<stdlib.h>
#include <SDL2/SDL.h>
#include <pthread.h>
#include <SDL2/SDL_mixer.h>
#include<time.h>
#include<regex.h>
#include "rogue.h"
// #include"rogue.h"
#define MAX_HEIGHT 49
#define MAX_WIDTH 190

typedef struct Position{
    int x;
    int y;
} Position;

typedef struct Weapon{
    Position *pos;
    char shape;
    char name[20];
    int attack;
} Weapon;

typedef struct Player{
    char name[50];
    char password[40];
    char email[60];
    int score;
    int color;
    char character;
} Player;

typedef struct Game{
    struct Level *levels[4];
    int clevel;
} Game;


typedef struct QueueNode{
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
    char symbol;
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
int playermove(Position *newpos, playerG *user);
void drawplayer(playerG *player);
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
void drawmonster(Monster* monst);
int SetStartPos(Monster *monster, Room *room);
int movemonster(Level *level);
int pathfinding(Position *start, Position *end);
int pathrand(Position *pos);
Monster* findmonst(Position* pos, Monster** monsters);
int gamehub(Level *level);
void drawlevel(Level *level);
int combat(playerG* player, Monster* monster, int ord);
void render(Game *game);
void pathFind(Position *start, Position *end);
void shuffleDirections(int directions[4][2]);





int load_players(Player players[], const char *filename);
int comparePlayers(const void *a, const void *b);
int loading_screen();
int main_menu(int height, int width);
int handle_inputs(int height, int width, Player players[]);
int OPTIONS(int height, int width);
int MUSIC_SELECTION(int height, int width);
void *play_music_background(void *arg);
// pthread_t music_thread;
void start_music(const char *music_file);
void play_music(const char *file);
void stop_music();
int SCORE_BOARD(int height, int width, Player players[]);
int new_player(int height, int width, Player players[]);
int checkpass(char password[]);
char *randompass();
int isValidEmail(const char *email);
int CHAR_DESIGN(int height, int width);
int start_menu(int height, int width, Player players[]);
int login(int height, int width, Player players[]);



#endif
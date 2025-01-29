// Hamed Alinezhad 403106335
#include <ncurses.h>
#include <stdlib.h>

typedef struct Player {
    int xpos;
    int ypos;
    int healthbar;
    int currentRoom;  // Track the current room
} Player;

int screensetup();
void mapsetup(int room);
Player *playersetup();
int handleinput(int ch, Player *player);
int playerMove(int y, int x, Player *player);

int main() {
    Player *Hamed;
    int ch;

    initscr();  // Initialize ncurses
    screensetup();
    mapsetup(1);  // Start in room 1
    Hamed = playersetup();

    while ((ch = getchar()) != 27) {  // 27 is the ESC key
        handleinput(ch, Hamed);
    }

    endwin();  // End ncurses mode
    free(Hamed);  // Free allocated memory

    return 0;
}

int screensetup() {
    printw("Hello World!");
    noecho();  // Disable echoing of characters
    refresh();
    getchar();  // Wait for user input
    mvprintw(0, 0, "                ");  // Clear the message
    return 1;
}

void mapsetup(int room) {
    // clear();  // Clear the screen to redraw the current room
    if (room == 1) {
        // Room 1
        mvprintw(3, 15, "-------------");
        mvprintw(4, 15, "|...........|");
        mvprintw(5, 15, "|...........|");
        mvprintw(6, 15, "|...........|");
        mvprintw(7, 15, "-+-----------");
    } else if (room == 2) {
        // Room 2
        mvprintw(8, 15, "|.|");
        mvprintw(9, 15, "|.|");
        mvprintw(10, 15, "-+-----------");
        mvprintw(11, 15, "|...........|");
        mvprintw(12, 15, "|...........|");
        mvprintw(13, 15, "|...........|");
        mvprintw(14, 15, "-------------");
    }
    refresh();
}

Player *playersetup() {
    Player *newPlayer = (Player *)malloc(sizeof(Player));
    if (newPlayer == NULL) {
        endwin();
        printf("Error: Memory allocation failed.\n");
        exit(1);
    }
    newPlayer->xpos = 18;
    newPlayer->ypos = 5;
    newPlayer->healthbar = 20;
    newPlayer->currentRoom = 1;  // Start in room 1

    mvprintw(newPlayer->ypos, newPlayer->xpos, "@");  // Display player
    move(newPlayer->ypos, newPlayer->xpos);  // Move cursor to player position
    refresh();

    return newPlayer;  // Return the allocated player
}

int handleinput(int ch, Player *player) {
    switch (ch) {
        case 'w':
        case 'W':
            playerMove(player->ypos - 1, player->xpos, player);
            break;
        case 'a':
        case 'A':
            playerMove(player->ypos, player->xpos - 1, player);
            break;
        case 's':
        case 'S':
            playerMove(player->ypos + 1, player->xpos, player);
            break;
        case 'd':
        case 'D':
            playerMove(player->ypos, player->xpos + 1, player);
            break;
        default:
            break;
    }
    return 1;  // Return 1 to indicate success
}

int playerMove(int y, int x, Player *player) {
    // Check for room transitions
    if (player->currentRoom == 1 && y == 7 && x == 16) {
        // Transition from Room 1 to Room 2
        player->currentRoom = 2;
        player->xpos = 16;  // Set new position in Room 2
        player->ypos = 8;
        mapsetup(2);  // Redraw map for Room 2
    } else if (player->currentRoom == 2 && y == 7 && x == 16) {
        // Transition from Room 2 to Room 1
        player->currentRoom = 1;
        player->xpos = 16;  // Set new position in Room 1
        player->ypos = 7;
        mapsetup(1);  // Redraw map for Room 1
    } else {
        // Boundary checks within the current room
        if (player->currentRoom == 1) {
            if (y < 4 || y > 6 || x < 16 || x > 26) {
                return 0;  // Prevent movement outside Room 1
            }
        } else if (player->currentRoom == 2) {
            if (y < 8 || y > 13 || x < 16 || x > 26) {
                return 0;  // Prevent movement outside Room 2
            }
        }

        // Move the player within the room
        mvprintw(player->ypos, player->xpos, ".");  // Clear the old position
        player->xpos = x;
        player->ypos = y;
        mvprintw(player->ypos, player->xpos, "@");  // Draw the player at the new position
        move(player->ypos, player->xpos);  // Move cursor to new position
        refresh();
    }

    return 1;  // Return 1 to indicate success
}

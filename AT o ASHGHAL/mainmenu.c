#include<stdio.h>
#include<ncurses.h>
#include<string.h>
#include<stdlib.h>
#include <SDL2/SDL.h>
#include <pthread.h>
#include <SDL2/SDL_mixer.h>
#include<time.h>
#include<regex.h>
// #include"rogue.h"
typedef struct Player{
    char name[50];
    char password[40];
    char email[60];
    int score;
    int color;
    char character;
} Player;
int load_players(Player players[], const char *filename);
int comparePlayers(const void *a, const void *b);
int loading_screen();
int main_menu(int height, int width);
int handle_input(int height, int width, Player players[]);
int OPTIONS(int height, int width);
int MUSIC_SELECTION(int height, int width);
void *play_music_background(void *arg);
pthread_t music_thread;
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

int main(){
    Player players[100];
    int player_num = load_players(players, "SCOREBOARD.txt");
    initscr();
    int height, width;
    getmaxyx(stdscr, height, width);
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();
    start_color();
    bkgd(COLOR_BLACK);
    loading_screen();
    start_music("01. Main Menu.mp3");
    int running = 1;
    while (running) {
        running = handle_input(height, width, players);
    }
    endwin();
    return 0;
}

int loading_screen(){
    mvprintw(14, 45, "                                                                                                       ");
    mvprintw(15, 45, "RRRRRRRRRRRRRRRRR        OOOOOOOOO             GGGGGGGGGGGGGUUUUUUUU     UUUUUUUUEEEEEEEEEEEEEEEEEEEE");
    mvprintw(16, 45, "R::::::::::::::::R     OO:::::::::OO        GGG::::::::::::GU::::::U     U::::::UE::::::::::::::::::::E");
    mvprintw(17, 45, "R::::::RRRRRR:::::R  OO:::::::::::::OO    GG:::::::::::::::GU::::::U     U::::::UE::::::::::::::::::::E");
    mvprintw(18, 45, "RR:::::R     R:::::RO:::::::OOO:::::::O  G:::::GGGGGGGG::::GUU:::::U     U:::::UUEE::::::EEEEEEEEE::::E");
    mvprintw(19, 45, "  R::::R     R:::::RO::::::O   O::::::O G:::::G       GGGGGG U:::::U     U:::::U   E:::::E       EEEEEE");
    mvprintw(20, 45, "  R::::R     R:::::RO:::::O     O:::::OG:::::G               U:::::D     D:::::U   E:::::E             ");
    mvprintw(21, 45, "  R::::RRRRRR:::::R O:::::O     O:::::OG:::::G               U:::::D     D:::::U   E::::::EEEEEEEEEE   ");
    mvprintw(22, 45, "  R:::::::::::::RR  O:::::O     O:::::OG:::::G    GGGGGGGGGG U:::::D     D:::::U   E:::::::::::::::E   ");
    mvprintw(23, 45, "  R::::RRRRRR:::::R O:::::O     O:::::OG:::::G    G::::::::G U:::::D     D:::::U   E:::::::::::::::E   ");
    mvprintw(24, 45, "  R::::R     R:::::RO:::::O     O:::::OG:::::G    GGGGG::::G U:::::D     D:::::U   E::::::EEEEEEEEEE   ");
    mvprintw(25, 45, "  R::::R     R:::::RO:::::O     O:::::OG:::::G        G::::G U:::::D     D:::::U   E:::::E             ");
    mvprintw(26, 45, "  R::::R     R:::::RO::::::O   O::::::O G:::::G       G::::G U::::::U   U::::::U   E:::::E       EEEEEE");
    mvprintw(27, 45, "RR:::::R     R:::::RO:::::::OOO:::::::O  G:::::GGGGGGGG::::G U:::::::UUU:::::::U EE::::::EEEEEEEE:::::E");
    mvprintw(28, 45, "R::::::R     R:::::R OO:::::::::::::OO    GG:::::::::::::::G  UU:::::::::::::UU  E::::::::::::::::::::E");
    mvprintw(29, 45, "R::::::R     R:::::R   OO:::::::::OO        GGG::::::GGG:::G    UU:::::::::UU    E::::::::::::::::::::E");
    mvprintw(30, 45, "RRRRRRRR     RRRRRRR     OOOOOOOOO             GGGGGG   GGGG      UUUUUUUUU      EEEEEEEEEEEEEEEEEEEEEE");
    mvprintw(40, 61, "___________");
    mvprintw(41, 61, "|__________| 10%%");
    refresh();
    napms(50);
    mvprintw(40, 61, "__________________");
    mvprintw(41, 61, "|________________| 20%%");
    refresh();
    napms(50);
    mvprintw(40, 61, "________________________");
    mvprintw(41, 61, "|______________________| 30%%");
    refresh();
    napms(50);
    mvprintw(40, 61, "______________________________");
    mvprintw(41, 61, "|____________________________| 40%%");
    refresh();
    napms(50);
    mvprintw(40, 61, "____________________________________");
    mvprintw(41, 61, "|__________________________________| 50%%");
    refresh();
    napms(50);
    mvprintw(40, 61, "__________________________________________");
    mvprintw(41, 61, "|________________________________________| 60%%");
    refresh();
    napms(50);
    mvprintw(40, 61, "________________________________________________");
    mvprintw(41, 61, "|______________________________________________| 70%%");
    refresh();
    napms(50);
    mvprintw(40, 61, "______________________________________________________");
    mvprintw(41, 61, "|____________________________________________________| 80%%");
    refresh();
    napms(50);
    mvprintw(40, 61, "____________________________________________________________");
    mvprintw(41, 61, "|__________________________________________________________| 90%%");
    refresh();
    napms(50);
    mvprintw(40, 61, "__________________________________________________________________");
    mvprintw(41, 61, "|________________________________________________________________| 100%%");
    refresh();
    napms(50);
    init_pair(1, COLOR_WHITE, COLOR_RED);
    mvprintw(40, 60, "                                                                      ");
    mvprintw(41, 60, "                                                                      \n");
    // attron(COLOR_PAIR(1));
    // attron(A_BLINK);
    mvprintw(41, 71, "WELCOME TO THE ROGUE! PRESS ANY KEY TO CONTINUE...");
    // attroff(COLOR_PAIR(1));
    refresh();

    getchar();
    return 1;
}
int main_menu(int ter_height, int ter_width) {
    clear();
    refresh();

    int height = ter_height * 3 / 5, width = ter_width * 3 / 5, starty = ter_height/5, startx = ter_width/5;
    WINDOW *menu_win = newwin(height, width, starty, startx);
    const char *menu_items[] = {"START THE GAME", "OPTIONS", "SCORE BOARD", "EXIT"};
    int n_items = sizeof(menu_items) / sizeof(menu_items[0]);
    int choice = 0;
    int key;

    box(menu_win, 0, 0);

    while (1) {
        werase(menu_win);
        box(menu_win, 0, 0); 

        mvwprintw(menu_win, 0, (width - 30) / 2, "  #### ROGUE MAIN MENU ####  ");
        mvwprintw(menu_win, 2, 3, "        _   ,_,   _");                                                
        mvwprintw(menu_win, 3, 3, "       / `'=) (='` \\");
        mvwprintw(menu_win, 4, 3, "      /.-.-.\\ /.-.-.\\ ");
        mvwprintw(menu_win, 5, 3, "      `      \"      `");            
        mvwprintw(menu_win, height - 7, 70, "      /| ________________");       
        mvwprintw(menu_win, height - 6, 70, "O|===|* >________________>");
        mvwprintw(menu_win, height - 5, 70, "      \\|");
        mvwprintw(menu_win, 3, 75, "                      ____    ");   
        mvwprintw(menu_win, 4, 75, "                     / ___`\\  ");  
        mvwprintw(menu_win, 5, 75, "         /|         ( (   \\ \\ ");  
        mvwprintw(menu_win, 6, 75, "    |^v^v  V|        \\ \\/) ) )");
        mvwprintw(menu_win, 7, 75, "    \\  ____ /         \\_/ / / ");  
        mvwprintw(menu_win, 8, 75, "    ,Y`    `,            / /  "); 
        mvwprintw(menu_win, 9, 75, "    ||  -  -)           { }   ");
        mvwprintw(menu_win, 10, 75, "    \\\\   _\\ |           | |   "); 
        mvwprintw(menu_win, 11, 75, "     \\\\ / _`\\_         / /    "); 
        mvwprintw(menu_win, 12, 75, "     / |  ~ | ``\\     _|_|    "); 
        mvwprintw(menu_win, 13, 75, "  ,-`  \\    |  \\ \\  ,//(_}    "); 
        mvwprintw(menu_win, 14, 75, " /      |   |   | \\/  \\| |    ");   
        mvwprintw(menu_win, 15, 75, "|       |   |   | '   ,\\ \\    ");
        mvwprintw(menu_win, 16, 75, "|     | \\   /  /\\  _/`  | |   "); 
        mvwprintw(menu_win, 17, 75, "\\     |  | |   | ``     | |   "); 
        mvwprintw(menu_win, 18, 75, " |    \\  \\ |   |        | |   "); 
        mvwprintw(menu_win, 19, 75, " |    |   |/   |        / /   ");
        mvwprintw(menu_win, 20, 75, " |    |        |        | |   "); 
        mvwprintw(menu_win, 20 - 12, 2, "          4$$-.                    ");                                                
        mvwprintw(menu_win, 21 - 12, 2, "           4   \".                 ");
        mvwprintw(menu_win, 22 - 12, 2, "           4    ^.                 ");
        mvwprintw(menu_win, 23 - 12, 2, "           4     $                 "); 
        mvwprintw(menu_win, 24 - 12, 2, "           4     'b                ");                                                
        mvwprintw(menu_win, 25 - 12, 2, "           4      \"b.             ");
        mvwprintw(menu_win, 26 - 12, 2, "           4        $              ");
        mvwprintw(menu_win, 27 - 12, 2, "           4        $r             "); 
        mvwprintw(menu_win, 28 - 12, 2, "           4        $F             ");                                                
        mvwprintw(menu_win, 29 - 12, 2, "-$b========4========$b====*P=>     ");
        mvwprintw(menu_win, 30 - 12, 2, "           4       *$$F            ");
        mvwprintw(menu_win, 31 - 12, 2, "           4        $$             "); 
        mvwprintw(menu_win, 32 - 12, 2, "           4       .$F             ");                                                
        mvwprintw(menu_win, 33 - 12, 2, "           4       do              ");
        mvwprintw(menu_win, 34 - 12, 2, "           4      P                ");
        mvwprintw(menu_win, 35 - 12, 2, "           4     2                 ");
        mvwprintw(menu_win, 36 - 12, 2, "           4    0                  ");
        mvwprintw(menu_win, 37 - 12, 2, "           J.  2                  ");
        mvwprintw(menu_win, 38 - 12, 2, "          '$$ 4                     ");

        for (int i = 0; i < n_items; i++) {
            if (i == choice) {
                wattron(menu_win, A_REVERSE);
                mvwprintw(menu_win, 6 + 5 * i, (width - 16) / 2, "%s", menu_items[i]);
                wattroff(menu_win, A_REVERSE);
            } else {
                mvwprintw(menu_win, 6 + 5 * i, (width - 16) / 2, "%s", menu_items[i]);
            }
        }
        wrefresh(menu_win);
        key = getch();
        switch (key) {
            case KEY_UP:
                choice--;
                if (choice < 0)
                    choice = n_items - 1;
                break;
            case KEY_DOWN:
                choice++;
                if (choice >= n_items)
                    choice = 0;
                break;
            case '\n':
                delwin(menu_win);
                return choice + 1;
        }
    }
    return 1;
}
int OPTIONS(int height, int width) {
    clear();
    refresh();
    const char *options[] = {
        "CHANGE MUSIC",
        "CHARACTER DESIGN",
        "ADJUST DIFFICULTY",
        "BACK"
    };
    int n_options = sizeof(options) / sizeof(options[0]);
    int selected = 0;
    int key;
    int current_music = 0;
    WINDOW *options_win = newwin(35, 100, (height - 35) / 2, (width - 80) / 2);
    // box(options_win, 0, 0);

    while (1) {
        mvwprintw(options_win, 2, 40, "    ###OPTIONS###    ");
        mvwprintw(options_win, 3, 40,   "                        @@@@                          ");                     
        mvwprintw(options_win, 4, 40,   "                       @@@@@@                         ");             
        mvwprintw(options_win, 5, 40,   "             @@@@    #@@@@@@@@@:   @@@@%%              ");             
        mvwprintw(options_win, 6, 40,   "           @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@             ");             
        mvwprintw(options_win, 7, 40,   "            @@@@@@@@@@@@@@@@@@@@@@@@@@@@              ");             
        mvwprintw(options_win, 8, 40,   "           @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@             ");             
        mvwprintw(options_win, 9, 40,   "       @@%%@@@@@@@@@@@*        +@@@@@@@@@@@@@@         ");             
        mvwprintw(options_win, 10, 40,   "    @@@@@@@@@@@@@%%                #@@@@@@@@@@@@@.     ");             
        mvwprintw(options_win, 11, 40,   "   @@@@@@@@@@@@=                    :@@@@@@@@@@@@:    ");             
        mvwprintw(options_win, 12, 40,   "    #@@@@@@@@@                        @@@@@@@@@@      ");             
        mvwprintw(options_win, 13, 40,   "     %%@@@@@@@                          #@@@@@@@       ");             
        mvwprintw(options_win, 14, 40,   "     @@@@@@@                            %%@@@@@@-      ");             
        mvwprintw(options_win, 15, 40,   "    @@@@@@@                              @@@@@@@      ");             
        mvwprintw(options_win, 16, 40,   "#@@@@@@@@@@                              @@@@@@@@@@*  ");             
        mvwprintw(options_win, 17, 40,   "+@@@@@@@@@@                              %%@@@@@@@@@*  ");             
        mvwprintw(options_win, 18, 40,   "+@@@@@@@@@@                              @@@@@@@@@@*  ");             
        mvwprintw(options_win, 19, 40,   "    @@@@@@@                              @@@@@@@      ");             
        mvwprintw(options_win, 20, 40,   "     @@@@@@@                            %%@@@@@@-      ");             
        mvwprintw(options_win, 21, 40,   "     %%@@@@@@@                          @@@@@@@@       ");             
        mvwprintw(options_win, 22, 40,   "    @@@@@@@@@@                        @@@@@@@@@@      ");             
        mvwprintw(options_win, 23, 40,   "   @@@@@@@@@@@@*                    =@@@@@@@@@@@@     ");             
        mvwprintw(options_win, 24, 40,   "    @@@@@@@@@@@@@@                %%@@@@@@@@@@@@@      ");             
        mvwprintw(options_win, 25, 40,   "     @#  #@@@@@@@@@@@%%        %%@@@@@@@@@@@@  =@       ");             
        mvwprintw(options_win, 26, 40,   "           @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@             ");             
        mvwprintw(options_win, 27, 40,   "            @@@@@@@@@@@@@@@@@@@@@@@@@@@@              ");             
        mvwprintw(options_win, 28, 40,   "           @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@             ");             
        mvwprintw(options_win, 29, 40,   "             @@@@    =@@@@@@@@*    @@@@=              ");             
        mvwprintw(options_win, 30, 40,   "                       @@@@@@                         ");             
        mvwprintw(options_win, 31, 40,   "                       -@@@@#                         ");            
        box(options_win, 0, 0);
        for (int i = 0; i < n_options; i++) {
            if (i == selected) {
                wattron(options_win, A_REVERSE);
                mvwprintw(options_win, 8 + 6 * i, 7, "%s", options[i]);
                wattroff(options_win, A_REVERSE);
            } else {
                mvwprintw(options_win, 8 + 6 * i, 7, "%s", options[i]);
            }
        }
        wrefresh(options_win);

        key = getch();
        switch (key) {
            case KEY_UP:
                selected--;
                if (selected < 0) selected = n_options - 1;
                break;
            case KEY_DOWN:
                selected++;
                if (selected >= n_options) selected = 0;
                break;
            case '\n':
                if (selected == 0) {
                    int current_music = MUSIC_SELECTION(height, width);
                    if (current_music == 1) {
                        start_music("c418_-_aria_math.mp3");
                    } else if (current_music == 2) {
                        start_music("rymykhs_ahng_amng_as.mp3");
                    } else if (current_music == 3) {
                        start_music("bad-piggies-theme.mp3");
                    } else if (current_music == 4) {
                        stop_music("bad-piggies-theme.mp3");
                    }
                    clear();
                    refresh();
                    break;
                } 
                else if (selected == 1){
                    int character_setup = CHAR_DESIGN(height, width);
                    wrefresh(options_win);
                }
                else if (selected == n_options - 1) {
                    delwin(options_win);
                    return 1;
                }
                break;
        }
    }
}
int MUSIC_SELECTION(int height, int width) {
    clear();
    refresh();

    const char *music_tracks[] = {
        "Track 1: ARIA MATH",
        "Track 2: AMONG US",
        "Track 3: BAD PIGGIES",
        "DISCONNECT"
    };
    int n_tracks = sizeof(music_tracks) / sizeof(music_tracks[0]);
    int selected = 0;
    int key;

    WINDOW *music_win = newwin(15, 40, (height - 15) / 2, (width - 40) / 2);
    box(music_win, 0, 0);

    while (1) {
        mvwprintw(music_win, 1, 2, "MUSIC SELECTION");
        for (int i = 0; i < n_tracks; i++) {
            if (i == selected) {
                wattron(music_win, A_REVERSE);
                mvwprintw(music_win, 3 + 2 * i, 2, "%s", music_tracks[i]);
                wattroff(music_win, A_REVERSE);
            } else {
                mvwprintw(music_win, 3 + 2 * i, 2, "%s", music_tracks[i]);
            }
        }
        wrefresh(music_win);

        key = getch();
        switch (key) {
            case KEY_UP:
                selected--;
                if (selected < 0) selected = n_tracks - 1;
                break;
            case KEY_DOWN:
                selected++;
                if (selected >= n_tracks) selected = 0;
                break;
            case '\n':
                return selected + 1; 
            case 27:
                return 0;
        }
    }
}
int SCORE_BOARD(int height, int width, Player players[]) {
    clear();
    refresh();
    FILE *scoreB = fopen("SCOREBOARD.txt", "r");
    if (!scoreB) {
        mvprintw(height / 2, (width - 20) / 2, "Unable to open scoreboard file!");
        refresh();
        getch();
        return 1;
    }    
    char dummy[100];
    int player_count = 0;

    while (fscanf(scoreB, "%s %s %s %d", players[player_count].name, 
                  players[player_count].password, dummy, &players[player_count].score) == 4) {
        player_count++;
        if (player_count >= 100) {
            break;
        }
    }
    fclose(scoreB);
    qsort(players, player_count, sizeof(Player), comparePlayers);
    WINDOW *score_win = newwin(40, 100, (height - 40) / 2, (width - 100) / 2);
    box(score_win, 0, 0);
    mvwprintw(score_win, 1, 2, "SCOREBOARD");

    mvwprintw(score_win, 5, 50, "                              ) ");  
    mvwprintw(score_win, 6, 50, "                           (\\/,\\");   
    mvwprintw(score_win, 7, 50, "                  ___,      )/(|");    
    mvwprintw(score_win, 8, 50, "                 /,===      \\\\//");    
    mvwprintw(score_win, 9, 50, "              ,==( \"|\"      (# )");    
    mvwprintw(score_win, 10, 50, "             ,==='\\_-/       :| ");    
    mvwprintw(score_win, 11, 50, "              ,---'  \\---.   || ");   
    mvwprintw(score_win, 12, 50, "             (     - -    )  |: ");    
    mvwprintw(score_win, 13, 50, "             |  \\_. '  _./\\ ,'/\\");      
    mvwprintw(score_win, 14, 50, "             |  )       / ,-||\\/");      
    mvwprintw(score_win, 15, 50, "   ___       ( < \\     (\\___/|| ");    
    mvwprintw(score_win, 16, 50, "  /   \\,----._\\ \\(   '  )    #; ");    
    mvwprintw(score_win, 17, 50, " (   /         \\|'',, ,'\\       ");   
    mvwprintw(score_win, 18, 50, " )   |          )\\   '   |      ");     
    mvwprintw(score_win, 19, 50, " (  (|     ,    \\_)      |      ");  
    mvwprintw(score_win, 20, 50, "  )  )\\     \\-.__\\   |_, /      ");   
    mvwprintw(score_win, 21, 50, "  ( (  \\    )  )  ]  |  (       ");  
    mvwprintw(score_win, 22, 50, "   ) ) _) _/ _/   /, )) /       ");   
    mvwprintw(score_win, 23, 50, "   (/  \\ <\\ \\      \\ |\\ |       ");   
    mvwprintw(score_win, 24, 50, "    ) ._) \\__\\_    ) | )(       ");  
    mvwprintw(score_win, 25, 50, "       )_,,\\ )_\\    )|<,_\\      ");   
    mvwprintw(score_win, 26, 50, "          )_\\      /_(  |_\\     ");   
    mvwprintw(score_win, 27, 50, "                    )_\\         ");      
    wrefresh(score_win);
    int line = 2;
    for (int i = 0; i < player_count && line < 18; i++) {
        mvwprintw(score_win, ++line, 2, "%-10s     %15d", players[i].name, players[i].score);
        wrefresh(score_win);
    }


    mvwprintw(score_win, 38, 39, "Press Esc to return...");
    wrefresh(score_win);
    char ch;
    while (1){
        ch = getchar();
        if (ch == 27){
            delwin(score_win);
            return 1;
        }
    }
}
int comparePlayers(const void *a, const void *b) {
    Player *playerA = (Player *)a;
    Player *playerB = (Player *)b;
    return playerB->score - playerA->score;
}
int handle_input(int height, int width, Player players[]) {
    while (1) {
        int selected_option = main_menu(height, width);

        switch (selected_option) {
            case 1:
                start_menu(height, width, players);
                break;
            case 2:
                while (1) {
                    int selected = OPTIONS(height, width);
                    if (selected == 1) {
                        break;
                    }
                }
                break;

            case 3:
                clear();
                SCORE_BOARD(height, width, players);
                break;

            case 4: {
                int confirm_selected = 0;
                int key;

                while (1) {
                    clear();
                    mvprintw(height / 2, width / 2 - 6, "ARE YOU SURE?");
                    
                    if (confirm_selected == 0) {
                        attron(A_BOLD | A_REVERSE);
                        mvprintw(height / 2 + 2, width / 2 - 6, "YES");
                        attroff(A_BOLD | A_REVERSE);
                        mvprintw(height / 2 + 2, width / 2 + 6, "NO");
                    } else {
                        mvprintw(height / 2 + 2, width / 2 - 6, "YES");
                        attron(A_BOLD | A_REVERSE);
                        mvprintw(height / 2 + 2, width / 2 + 6, "NO");
                        attroff(A_BOLD | A_REVERSE);
                    }

                    refresh();
                    key = getch();
                    switch (key) {
                        case KEY_LEFT:
                            confirm_selected = 0;
                            break;
                        case KEY_RIGHT:
                            confirm_selected = 1;
                            break;
                        case '\n':
                            if (confirm_selected == 0) {
                                clear();
                                mvprintw(height / 2, width / 2 - 4, "EXITING...");
                                refresh();
                                napms(2000);
                                endwin();
                                return 0;
                            } else if (confirm_selected == 1) {
                                return 1;
                            }
                            break;
                    }
                }
                break;
            }

            default:
                break;
        }
    }
}
void *play_music_background(void *arg) {
    const char *music_file = (const char *)arg;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! Mix_Error: %s\n", Mix_GetError());
        return NULL;
    }

    Mix_Music *music = Mix_LoadMUS(music_file);
    if (!music) {
        printf("Error loading music: %s\n", Mix_GetError());
        return NULL;
    }

    if (Mix_PlayMusic(music, -1) == -1) {
        printf("Error playing music: %s\n", Mix_GetError());
    }
    while (Mix_PlayingMusic()) {
        SDL_Delay(100); 
    }

    Mix_FreeMusic(music);
    Mix_CloseAudio();
    return NULL;
}
void play_music(const char *file) {
    Mix_Music *music = Mix_LoadMUS(file);
    if (!music) {
        printf("Failed to load music: %s\n", Mix_GetError());
        return;
    }

    Mix_PlayMusic(music, -1);
}
void stop_music() {
    Mix_HaltMusic();          
    pthread_cancel(music_thread);
    pthread_join(music_thread, NULL); 
}
void start_music(const char *music_file) {
    if (pthread_create(&music_thread, NULL, play_music_background, (void *)music_file) != 0) {
        printf("Failed to create music thread\n");
    }
}
int new_player(int height, int width, Player players[]) {
    clear();
    refresh();
    FILE *player_data = fopen("SCOREBOARD.txt", "a+");
    if (!player_data) {
        mvprintw(height / 2, (width - 20) / 2, "Unable to open scoreboard file!");
        refresh();
        getch();
        return 1;
    }

    int player_count = 0;
    while (fscanf(player_data, "%s", players[player_count].name) == 1) {
        player_count++;
        if (player_count >= 100) {
            break;
        }
    }
    WINDOW *new_player_win = newwin(30, 80, (height - 30) / 2, (width - 80) / 2);
    box(new_player_win, 0, 0);

    char *info[] = {"USER NAME:", "PASSWORD:", "EMAIL:"};
    int n_options = sizeof(info) / sizeof(info[0]);
    int selected = 0;
    int key;

    char USERNAME[50] = {0};
    char PASSWORD[50] = {0};
    char EMAIL[60] = {0};

    while (1) {
        mvwprintw(new_player_win, 1, 2, "FILL OUT THE INFORMATION:");
        mvwprintw(new_player_win, 16, 14, "PASSWORD MUST HAVE AT LEAST 7 CHARACTERS!");
        mvwprintw(new_player_win, 18, 14, "YOU HAVE TO USE AT LEAST 1 UPPERCASE AND 1 LOWERCASE!");
        mvwprintw(new_player_win, 20, 14, "(PRESS R TO GENERATE RANDOM PASSWORD) ");
        mvwprintw(new_player_win, 1, 52, "PRESS S TO SAVE!");
        mvwprintw(new_player_win, 28, 30, "PRESS ESC TO RETURN...");
        for (int i = 0; i < n_options; i++) {
            if (i == selected) {
                wattron(new_player_win, A_REVERSE);
                mvwprintw(new_player_win, 5 + 9 * i, 2, "%s", info[i]);
                wattroff(new_player_win, A_REVERSE);
            } else {
                mvwprintw(new_player_win, 5 + 9 * i, 2, "%s", info[i]);
            }
        }
        wrefresh(new_player_win);

        key = getch();
        switch (key) {
            case KEY_UP:
                selected--;
                if (selected < 0) selected = n_options - 1;
                break;
            case KEY_DOWN:
                selected++;
                if (selected >= n_options) selected = 0;
                break;
            case '\n': 
                echo();
                if (selected == 0) {
                    mvwprintw(new_player_win, 5, 14, "                 ");
                    curs_set(1);
                    wmove(new_player_win, 5, 14);
                    wrefresh(new_player_win);

                    while (1) {
                        wgetnstr(new_player_win, USERNAME, sizeof(USERNAME) - 1);
                        int username_exists = 0;

                        for (int i = 0; i < player_count; i++) {
                            if (strcmp(players[i].name, USERNAME) == 0) {
                                username_exists = 1;
                                break;
                            }
                        }

                        if (username_exists) {
                            mvwprintw(new_player_win, 5, 14, "                 ");
                            mvwprintw(new_player_win, 7, 14, "USERNAME NOT AVAILABLE!");
                            wrefresh(new_player_win);
                            wmove(new_player_win, 5, 14); 
                            continue;
                        } else {
                            mvwprintw(new_player_win, 7, 14, "                           ");
                            wrefresh(new_player_win);
                            break;
                        }
                    }
                    curs_set(0);
                } else if (selected == 1) { 
                    mvwprintw(new_player_win, 14, 14, "                              "); 
                    curs_set(1);
                    while (1){
                        wmove(new_player_win, 14, 14); 
                        wrefresh(new_player_win);
                        wgetnstr(new_player_win, PASSWORD, sizeof(PASSWORD) - 1);
                        if (strlen(PASSWORD) < 7){
                            mvwprintw(new_player_win, 14, 14, "                         ");
                            mvwprintw(new_player_win, 12, 14, "INVALID PASSWORD!");
                            wrefresh(new_player_win);
                            wmove(new_player_win, 12, 14);
                            break;
                        }
                        else if (checkpass(PASSWORD) == 0){
                            mvwprintw(new_player_win, 14, 14, "                        ");
                            mvwprintw(new_player_win, 12, 14, "INVALID PASSWORD!");
                            wrefresh(new_player_win);
                            wmove(new_player_win, 14, 14);
                            break;
                        }
                        else {
                                mvwprintw(new_player_win, 12, 14, "                                                     ");
                                wrefresh(new_player_win);
                                break; 
                        }
                    }
                    curs_set(0);
                } else if (selected == 2) { 
                    mvwprintw(new_player_win, 23, 14, "                                                ");
                    curs_set(1);
                    while (1){
                        wmove(new_player_win, 23, 14); 
                        wrefresh(new_player_win);
                        wgetnstr(new_player_win, EMAIL, sizeof(EMAIL) - 1);
                        if (isValidEmail(EMAIL) == 0){
                            mvwprintw(new_player_win, 23, 14, "                     ");
                            mvwprintw(new_player_win, 25, 14, "INVALID EMAIL FORMAT!");
                            wrefresh(new_player_win);
                            wmove(new_player_win, 23, 14);
                            break;
                        }
                        else{
                            // mvwprintw(new_player_win, 23, 14, "                                        ");
                            wrefresh(new_player_win);
                            break; 
                        }
                    }
                    curs_set(0);
                }
                noecho();
                break;
            case 'r':
                if (selected == 1) {
                    char *random_pass = (char*)malloc(20 * sizeof(char));
                    random_pass = randompass();
                    strcpy(PASSWORD, random_pass);
                    mvwprintw(new_player_win, 14, 14, "                              ");
                    mvwprintw(new_player_win, 14, 14, "%s", PASSWORD);
                    wrefresh(new_player_win);
                }
                break;
            case 'S':
            case 's':
                if (strlen(USERNAME) > 0 && strlen(PASSWORD) > 0 && strlen(EMAIL) > 0 && isValidEmail(EMAIL) == 1 && checkpass(PASSWORD) == 1 && strlen(PASSWORD) > 6) {
                    fprintf(player_data, "%s    %s    %s\n", USERNAME, PASSWORD, EMAIL);
                    fflush(player_data);
                    fclose(player_data);
                    delwin(new_player_win);
                    return 0;
                } else {
                    mvwprintw(new_player_win, 25, 2, "ALL FIELDS MUST BE FILLED CORRECTLY!");
                    wrefresh(new_player_win);
                }
                break;
            case 27:
                delwin(new_player_win);
                return 0;
                break;
        }
    }
}
int checkpass(char password[]){
    int hasU  = 0;
    int hasL = 0;
    int passlen = strlen(password);
    for (int i = 0; i < passlen; i++){
        if (password[i] >= 'A' && password[i] <= 'Z'){
            hasU = 1;
        }
    }
    for (int i = 0; i < passlen; i++){
        if (password[i] >= 'a' && password[i] <= 'z'){
            hasL = 1;
        }
    }
    if (hasU && hasL){
        return 1;
    }
    return 0;
}
char *randompass(){
    srand(time(0));
    int a = rand() % 5 + 7;
    char *password = (char*)malloc(a * sizeof(char));
    char upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char lower[] = "abcdefghijklmnopqrstuvwxyz";
    char digits[] = "0123456789";
    int hasU = 0, hasL = 0;
    for (int i = 0; i < a; i++){
        int choice = rand() % 3;  // Choose character category
        switch (choice) {
            case 0:
                password[i] = lower[rand() % strlen(lower)];
                hasL = 1;
                break;
            case 1:
                password[i] = upper[rand() % strlen(upper)];
                hasU = 1;
                break;
            case 2:
                password[i] = digits[rand() % strlen(digits)];
                break;
        }
    }
    int x = rand() % a;
    int y = rand() % a;
    if (x == y){
        x--;
    }
    if (hasL == 0){
        password[x] = lower[rand() % strlen(lower)];
        hasL = 1;
    }
    if (hasU == 0){
        password[y] = upper[rand() % strlen(upper)];
        hasU = 1;
    }
    password[a] = '\0';
    return password;
}
int isValidEmail(const char *email) {
    const char *pattern = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";
    regex_t regex;
    int result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }
    result = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);
    if (result == 0) {
        return 1;  // Valid email
    } else {
        return 0;  // Invalid email
    }
}
int CHAR_DESIGN(int height, int width){
    clear();
    refresh();
    WINDOW *ch_des = newwin(25, 60, (height - 25) / 2, (width - 60) / 2);
    char *colors[] = {"RED", "BLUE", "GREEN", "YELLOW", "WHITE", "CHARACTER:"};
    int num = sizeof(colors) / sizeof(colors[0]);
    int selected = 0;
    int key;

    // Initialize color pairs
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    init_pair(3, COLOR_WHITE, COLOR_GREEN);
    init_pair(4, COLOR_WHITE, COLOR_YELLOW);
    init_pair(5, COLOR_BLACK, COLOR_WHITE);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);

    box(ch_des, 0, 0);
    char character;
    while (1) {
        mvwprintw(ch_des, 1, 2, "CHARACTER DESIGN");
        
        // Print colors horizontally
        for (int i = 0; i < num; i++) {
            if (i == selected) {
                wattron(ch_des, COLOR_PAIR(i + 1) | A_UNDERLINE); // Bold and color for selected
            } else {
                wattron(ch_des, COLOR_PAIR(i + 1));          // Just color for others
            }
            mvwprintw(ch_des, 10, 2 + i * 8, "%s", colors[i]); // Horizontal arrangement
            wattroff(ch_des, COLOR_PAIR(i + 1) | A_UNDERLINE);        // Turn off attributes
        }
        mvwprintw(ch_des, 21, 2, "PRESS ESC TO EXIT");
        wrefresh(ch_des);
        key = getch();
        switch (key) {
            case KEY_LEFT:
                selected--;
                if (selected < 0) {
                    selected = num - 1; // Wrap around
                }
                break;
            case KEY_RIGHT:
                selected++;
                if (selected >= num) {
                    selected = 0; // Wrap around
                }
                break;
            case '\n': // ENTER key            
                if (selected == 5){
                    echo();
                    while (1){
                        mvwprintw(ch_des, 10, 53, "   ");
                        wmove(ch_des, 10, 53);
                        curs_set(1);
                        character = wgetch(ch_des);
                        mvwprintw(ch_des, 12, 35, "CHARACTER CHOSEN: %c  ", character);
                        wrefresh(ch_des);
                        break;
                    }
                    noecho();
                    curs_set(0);
                }
                break;
            case 27: // ESC key
                werase(ch_des); // Erase window contents
                wrefresh(ch_des); // Refresh to reflect changes
                delwin(ch_des);   // Delete the window
                clear();          // Clear the main screen
                refresh(); 
                return 0;
                break;
        }
    }
}
int start_menu(int height, int width, Player players[]){
    clear();
    refresh();
    char *options[] = {" PLAY AS A GUEST ", "    NEW PLAYER    ", "      LOGIN      ", "BACK TO MAIN MENU"};
    int num = sizeof(options) / sizeof(options[0]);
    int selected = 0;
    int key;
    WINDOW *start_menu = newwin(40, 120, (height - 40) / 2, (width - 120) / 2);
    mvwprintw(start_menu, 2, 52, "  ###START MENU###  ");
    mvwprintw(start_menu, 4, 40, "                            ==(W{==========-      /===-                        ");
    mvwprintw(start_menu, 5, 40, "                              ||  (.--.)         /===-_---~~~~~~~~~------____  ");
    mvwprintw(start_menu, 6, 40, "                              | \\_,|**|,__      |===-~___                _,-' `");
    mvwprintw(start_menu, 7, 40, "                 -==\\\\        `\\ ' `--'   ),    `//~\\\\   ~~~~`---.___.-~~      ");
    mvwprintw(start_menu, 8, 40, "             ______-==|        /`\\_. .__/\\ \\    | |  \\\\           _-~`         ");
    mvwprintw(start_menu, 9, 40, "       __--~~~  ,-/-==\\\\      (   | .  |~~~~|   | |   `\\        ,'             ");
    mvwprintw(start_menu, 10, 40, "    _-~       /'    |  \\\\     )__/==0==-\\<>/   / /      \\      /               ");
    mvwprintw(start_menu, 11, 40, "  .'        /       |   \\\\      /~\\___/~~\\/  /' /        \\   /'                ");
    mvwprintw(start_menu, 12, 40, " /  ____  /         |    \\`\\.__/-~~   \\  |_/'  /          \\/'                  ");
    mvwprintw(start_menu, 13, 40, "/-'~    ~~~~~---__  |     ~-/~         ( )   /'        _--~`                   ");
    mvwprintw(start_menu, 14, 40, "                  \\_|      /        _) | ;  ),   __--~~                        ");
    mvwprintw(start_menu, 15, 40, "                    '~~--_/      _-~/- |/ \\   '-~ \\                            ");
    mvwprintw(start_menu, 16, 40, "                   {\\__--_/}    / \\\\_>-|)<__\\      \\                           ");
    mvwprintw(start_menu, 17, 40, "                   /'   (_/  _-~  | |__>--<__|      |                          ");
    mvwprintw(start_menu, 18, 40, "                  |o-o /) )-~     | |__>--<__|      |                          ");
    mvwprintw(start_menu, 19, 40, "                  / /~ ,_/       / /__>---<__/      |                          ");
    mvwprintw(start_menu, 19, 40, "                  (- _//)       /-~_>---<__-~      /                           ");
    mvwprintw(start_menu, 20, 40, "                 (^(~          /~_>---<__-      _-~                            ");
    mvwprintw(start_menu, 21, 40, "                ,/|           /__>--<__/     _-~                               ");
    mvwprintw(start_menu, 22, 40, "             ,//('(          |__>--<__|     /  -               .----_          ");
    mvwprintw(start_menu, 23, 40, "            ( ( '))          |__>--<__|    |                 /' _---_~\\        ");
    mvwprintw(start_menu, 24, 40, "         `-)) )) (           |__>--<__|    |               /'  /     ~\\`\\      ");
    mvwprintw(start_menu, 25, 40, "        ,/,'//( (             \\__>--<__\\    \\            /'  //        ||      ");
    mvwprintw(start_menu, 26, 40, "      ,( ( ((, ))              ~-__>--<_~-_  ~--____---~' _/'/        /'       ");
    mvwprintw(start_menu, 27, 40, "    `~/  )` ) ,/|                 ~-_~>--<_/-__       __-~ _/                  ");
    mvwprintw(start_menu, 28, 40, "  ._-~//( )/ )) `                    ~~-'_/_/ /~~~~~~~__--~                    ");
    mvwprintw(start_menu, 29, 40, "   ;'( ')/ ,)(                              ~~~~~~~~~~                         ");
    mvwprintw(start_menu, 30, 40, "  ' ') '( (/                                                                   ");
    mvwprintw(start_menu, 31, 40, "    '   '  `                                                                   ");
    while (1){
        wrefresh(start_menu);
        box(start_menu, 0, 0);
        for (int i = 0; i < num; i++) {
            if (i == selected) {
                wattron(start_menu, A_REVERSE);
                mvwprintw(start_menu, 8 + 7 * i, 10, "%s", options[i]);
                wattroff(start_menu, A_REVERSE);
            } else {
                mvwprintw(start_menu, 8 + 7 * i, 10, "%s", options[i]);
            }
        }
        wrefresh(start_menu);
        key = getch();
        switch (key) {
            case KEY_UP:
                selected--;
                if (selected < 0) selected = num - 1;
                break;
            case KEY_DOWN:
                selected++;
                if (selected >= num) selected = 0;
                break;
            case '\n': 
                if (selected == 0){ //! FILL!!!!
                    start();
                }
                else if (selected == 1){
                    new_player(height, width, players);
                    continue;
                    // wrefresh(start_menu);
                }
                else if (selected == 2){
                    login(height, width, players);
                    continue;
                }
                else if (selected == 3){
                    return 0;
                    break;
                }
        }
    }
}
int login(int height, int width, Player players[]) {
    clear();
    refresh();
    FILE *player_data = fopen("SCOREBOARD.txt", "r"); // Open file in read mode
    if (!player_data) {
        mvprintw(height / 2, (width - 20) / 2, "Unable to open scoreboard file!");
        refresh();
        getch();
        return 1;
    }

    int player_count = 0;
    while (fscanf(player_data, "%s %s", players[player_count].name, players[player_count].password) == 2) {
        player_count++;
        if (player_count >= 100) {
            break;
        }
    }
    fclose(player_data);

    char *options[] = {"ENTER THE GAME", "USERNAME:", "PASSWORD:", "BACK"};
    int num = sizeof(options) / sizeof(options[0]);
    int selected = 0;
    int key;
    char pass[40] = {0};
    char user[40] = {0};
    int user_index = -1; // To track the index of the matching username

    WINDOW *login_win = newwin(30, 80, (height - 30) / 2, (width - 80) / 2);
    while (1) {
        wrefresh(login_win);
        box(login_win, 0, 0);
        for (int i = 0; i < num; i++) {
            if (i == selected) {
                wattron(login_win, A_REVERSE);
                mvwprintw(login_win, 3 + 7 * i, 12, "%s", options[i]);
                wattroff(login_win, A_REVERSE);
            } else {
                mvwprintw(login_win, 3 + 7 * i, 12, "%s", options[i]);
            }
        }
        wrefresh(login_win);
        key = getch();
        switch (key) {
            case KEY_UP:
                selected--;
                if (selected < 0) selected = num - 1;
                break;
            case KEY_DOWN:
                selected++;
                if (selected >= num) selected = 0;
                break;
            case '\n':
                if (selected == 1) { // Handle Username Input
                    mvwprintw(login_win, 10, 22, "                     ");
                    curs_set(1);
                    echo();
                    wmove(login_win, 10, 22);
                    wrefresh(login_win);
                    wgetnstr(login_win, user, sizeof(user) - 1);

                    user_index = -1; // Reset the index
                    for (int i = 0; i < player_count; i++) {
                        if (strcmp(players[i].name, user) == 0) {
                            user_index = i; // Store the index of the matching username
                            break;
                        }
                    }

                    if (user_index == -1) {
                        mvwprintw(login_win, 12, 22, "USERNAME NOT FOUND");
                        mvwprintw(login_win, 10, 22, "                     ");
                        wrefresh(login_win);
                    } else {
                        mvwprintw(login_win, 12, 22, "                             ");
                        wrefresh(login_win);
                    }
                    curs_set(0);
                    noecho();
                } else if (selected == 2) { // Handle Password Input
                    if (user_index == -1) { // No username entered/found yet
                        mvwprintw(login_win, 20, 22, "ENTER A VALID USERNAME FIRST!");
                        wrefresh(login_win);
                        continue;
                    }

                    mvwprintw(login_win, 17, 22, "                     ");
                    curs_set(1);
                    echo();
                    wmove(login_win, 17, 22);
                    wrefresh(login_win);
                    wgetnstr(login_win, pass, sizeof(pass) - 1);

                    if (strcmp(players[user_index].password, pass) == 0) {
                        mvwprintw(login_win, 20, 22, "                                     ");
                        wrefresh(login_win);
                    } else {
                        mvwprintw(login_win, 20, 22, "PASSWORD IS WRONG! TRY AGAIN");
                        wrefresh(login_win);
                    }
                    curs_set(0);
                    noecho();
                } else if (selected == 3) {
                    delwin(login_win);
                    return 0; // Back to previous menu
                }
                break;
        }
    }
}

int load_players(Player players[], const char *filename) {
    FILE *file = fopen("SCOREBOARD.txt", "r"); // Open the file in read mode
    if (!file) {
        printf("Error: Could not open file %s.\n", filename);
        return 0; // Return 0 if the file can't be opened
    }

    int count = 0; // Counter to track the number of players loaded
    while (count < 20 && fscanf(file, "%s %s %s %d %d %c", 
            players[count].name, 
            players[count].password, 
            players[count].email, 
            &players[count].score, 
            &players[count].color, 
            &players[count].character) == 6) {
        count++; // Increment the count for each player
    }

    fclose(file); // Close the file
    return count; // Return the number of players loaded
}

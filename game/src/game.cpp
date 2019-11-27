#include <unistd.h>
#include <ncurses.h>

#include <cstdint>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "game.h"
#include "JagumonData.h"

WINDOW* main_window;
WINDOW* game_window;

rect game_area;
rect screen_area;

vec2ui cur_size;

int init() {
    
    srand(time(0));

    initscr();

    cbreak();
    noecho();
    clear();
    refresh();

    curs_set(0);

    start_color();

    // read in window size
    cur_size = { 0, 0 };
    getmaxyx(main_window, cur_size.x, cur_size.y);

    // define area for screen (default terminal size)
    screen_area = { { 0, 0 }, { 80, 24 } };

    // set screen size accordingly
    wresize(main_window, screen_area.height(), screen_area.width());

    // initialize window areas
    int infopanel_height = 4;
    game_window = newwin(screen_area.height() - infopanel_height - 2, screen_area.width() - 2, screen_area.top() + 1, screen_area.left() + 1);
    main_window = newwin(screen_area.height(), screen_area.width(), 0, 0);

    // define area for movement
    game_area = { { 0, 0}, { screen_area.width() - 2, screen_area.height() - infopanel_height - 4 } };

    applyColorscheme(COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_GREEN);
    init_pair(3, COLOR_WHITE, COLOR_YELLOW);
    init_pair(4, COLOR_WHITE, COLOR_RED);
    init_pair(5, COLOR_WHITE, COLOR_BLUE);

    // enable function keys
    keypad(main_window, true);
    keypad(game_window, true);

    // disable input blocking
    nodelay(main_window, true);
    nodelay(game_window, true);

    // enable color
    if(!has_colors()) {
        endwin();
        printf("ERROR: Terminal does not support color.\n");
        exit(1);
    }

    return 0;
}



void run() {
    
    int tick = 0;
    int in_char = 0;
    bool exit_requested = false;
    bool game_over = false;
   
    // draw frame around whole screen
    wattron(main_window, A_BOLD);
    box(main_window, 0, 0);
    wattroff(main_window, A_BOLD);

    // draw dividing line between game and stats
    wmove(main_window, game_area.bot() + 3, 1);
    whline(main_window, '-', screen_area.width() - 2);

    // initial draw
    wrefresh(main_window);
    wrefresh(game_window);


    const std::vector<std::string> story_text = { 
        "In a galaxy far far away, somewhere in Kwangwoon...", 
        "You were peacefully working on your JaGu project... until...",
        "WHAAAAAAAAAAAM!!!!!", 
        "Jagumons appeared out of nowhere!!!",
        "And JeoGyeo is asking for a fight! Bright it on!!!!!!!!!"
    };


    mvwprintw(main_window, 22, 62, "SPACE(next) -->"); 

    tick = 0;
    size_t story_part = 0;
    size_t story_position = 0;

    while(1) {
        werase(game_window);
        in_char = wgetch(main_window);

        if(story_position < story_text[story_part].length()) {
            wattron(main_window, A_BOLD);
            mvwaddch(main_window, 20, 5 + story_position, story_text[story_part][story_position]);
            wattroff(main_window, A_BOLD);
            story_position++;
        }

        if(in_char == ' ') {
            story_part++;
            story_position = 0;
            mvwhline(main_window, 20, 1, ' ', screen_area.width() - 2);
        }

        else if(in_char == 'q') {
            exit_requested = true;
            break;
        }

        if(story_part >= story_text.size()) break;
        
        wrefresh(game_window);

        tick++;
        usleep(10000); // 1 ms
    }

    // white-out
    mvwhline(main_window, 22, 57, ' ', 22); 

    tick = 0;
    while(1) {

        // clear game window
        werase(game_window);
 
        // TODO: Give warning message if screen is too small!
        if(cur_size.x > screen_area.width() || cur_size.y > screen_area.height()) {}
        //winResize(cur_width, cur_height);
    
        // read in input key, if any (non-blocking as defined earlier)
        in_char = wgetch(main_window);
        in_char = tolower(in_char);

        switch(in_char) {
            case 'q': 
            case KEY_UP:
            case 'w':
            case 'i':
            case KEY_DOWN:
            case 's':
            case 'k':
            case KEY_LEFT: 
            case 'a':
            case 'j':
            case KEY_RIGHT: 
            case 'd':
            case 'l':
                exit_requested = true; 
                break;
            default: 
                break;
        }


        // draw UI elements
        // energy bar
        wmove(main_window, 20, 1);
        whline(main_window, ' ', 25); // health bar is 25 chars long
        wmove(main_window, 20, 1);
        drawEnergyBar(AAA.showStamina());

        // draw static string to hold percentage
        mvwprintw(main_window, 21, 1, " - S T A M I N A -     //");

        // draw numeric percentage
        wattron(main_window, A_BOLD);
        if(AAA.showStamina() <= 25) {
          wattron(main_window, COLOR_PAIR(4));
          if(tick % 100 < 50)
            mvwprintw(main_window, 21, 18, "%i%%", AAA.showStamina()); 
          wattroff(main_window, COLOR_PAIR(4));
        } else
            mvwprintw(main_window, 21, 18, "%i%%", AAA.showStamina()); 
        wattroff(main_window, A_BOLD);

        //usleep(100);

        // refresh windows
        wrefresh(main_window);
        wrefresh(game_window);


        if(game_over) {

            // store an approx location where text will be centered
            const int xpos = game_area.width() / 2 - 6; 
            const int ypos = game_area.height() / 2 - 2;

            // erase current game content on window and redraw a clean window
            werase(main_window);
            wattron(main_window, A_BOLD);
            box(main_window, 0, 0);
            wattroff(main_window, A_BOLD);

            wmove(main_window, game_area.bot() + 3, 1);
            whline(main_window, '-', screen_area.width() -2);

            wrefresh(main_window);
            wrefresh(game_window);

            // TODO print out score 
            // print game over prompt 
            mvwprintw(game_window, ypos, xpos , "GAME OVER");
            mvwprintw(game_window, ypos + 2, xpos - 7, "Press SPACE to play again");
            mvwprintw(game_window, ypos + 4, xpos - 7, "Press 'q' to quit the game");

            // loop until player either quits or restarts game
            while(1) {
                in_char = wgetch(main_window);

                if(in_char == ' ') { // reset all variables and restart game
                    tick = 0;
                    in_char = 0;
                    game_over = false;
                    exit_requested = false;
                    break;
                }

                else if(in_char == 'q') {
                    exit_requested = true;
                    break;
                }

                wrefresh(game_window);

                tick++;
                usleep(10000); // 1 ms
            }
        }

        if(exit_requested) break;

        tick++;

        //nanosleep({0, 1000000000}, NULL);
        usleep(10000); // 1 ms
    };

    delwin(main_window);

    endwin();

    // if(game_over) printf("Game over!\n");
}



void applyColorscheme(short fg, short bg) {
    init_pair(1, fg, bg);
    wbkgd(main_window, COLOR_PAIR(1));
    wbkgd(game_window, COLOR_PAIR(1));
}



void setFrame(){
    // creates simple frame around window composed of vertical and horizontal lines
    attron(A_BOLD);
    box(main_window, 0, 0);
    attroff(A_BOLD);
    
    // border characters can be set manually using the border function
    // border( wnd, leftside, rightside, topside, bottom side, tlcorner, 
    //                                      trcorner, blcorner, brcorner);
}



void winResize(int &orig_width, int &orig_height){
    int new_width, new_height;

    getmaxyx(main_window, new_width, new_height); 

    // if window dimensions have changed, update border
    if(new_width != orig_width || new_height != orig_height){
        orig_width = new_width;
        orig_height = new_height;
        
        wresize(main_window, new_height, 0);
        mvwin(main_window, new_height, 0);
        
        wclear(main_window);
        setFrame();
    }

}



void drawEnergyBar(int a) {

    int col_pair = 1;
    for(int i = 0; i < a; i+=4) {
        if(i > 100)
            col_pair = 5; // blue
        else if(i > 50)
            col_pair = 2; // green
        else if(i > 25)
            col_pair = 3; // yellow
        else
            col_pair = 4; // red

        wattron(main_window, COLOR_PAIR(col_pair));
        wattron(main_window, A_BOLD);
        waddch(main_window, '/');
        wattroff(main_window, A_BOLD);
        wattroff(main_window, COLOR_PAIR(col_pair));
    }
}

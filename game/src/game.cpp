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
    int choo_char = 0; // selecting Jagumon in CHOOSE JAGUMON PHASE
    int in_char = 0; // selecting action in BATTLE PHASE
    int finger = 0; // point at the Jagumon of Player's choice
    bool exit_flag = false; // when True, immediately finish the game
    bool game_over = false; // LOST T^T

    int party = 0; 	// n-th place in player's party. Starts at -1 because
			// it immediately rises as player chooses Jagumon
   
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
            exit_flag = true;
            break;
        }

        if(story_part >= story_text.size()) break;
        
        wrefresh(game_window);

        tick++;
        usleep(10000); // 1 ms
    }

    // white-out
    mvwhline(main_window, 22, 57, ' ', 22); 
    
    // ----------CHOOSE JAGU PHASE---------
    tick = 0;
    while(1) {
	// clear game, main window
	werase(game_window);

	// read input, set them all to lower case
	choo_char = wgetch(main_window);
	choo_char = tolower(choo_char);

	switch(choo_char) {
	    case 'a':
		if(finger>0) finger--;
		else finger=10;
		break;
	    case 'd':
		if(finger<9) finger++;
		else finger=0;
		break;
	    case 'q':
		exit_flag = true;
		break;
	    case ' ':
		party++;
		User[party] = jagumon[finger];
        	mvwprintw(game_window, 12, 10, User.at(party).showName());
		break;
	    default:
		break;
	}

	for(int i=0; i<10; i++) {
          mvwprintw(game_window, 2+i, 10, jagumon[i].showName());
	}
	mvwprintw(game_window, 2+finger, 9, ">");
	
	// refresh windows
	wrefresh(main_window);
	wrefresh(game_window);

	if(exit_flag) break;
	

	tick++;
	
	usleep(10000); //1ms
    }

    // ----------- BATTLE PHASE -----------
    tick = 0;
    while(1) {

	// TODO check if Jagumons are alive. If not, gameover.
        // clear game window
        werase(game_window);
 
	// read input, set them all to lower case
        in_char = wgetch(main_window);
        in_char = tolower(in_char);

        switch(in_char) { 
            case KEY_UP:
            case 'w':
            case 'i':
            case KEY_DOWN:
            case 's':
            case 'k':
            case KEY_LEFT: 
            case 'j':
            case KEY_RIGHT: 
            case 'l':
	        break;
	    case 'd':
		break;
	    case 'a':
	        break;
	    case 'q':
                exit_flag = true; 
                break;
            default: 
                break;
        }


        // draw UI elements
        // energy bar
        wmove(game_window, 1, 10);
        whline(game_window, ' ', 25); // health bar is 25 chars long
        wmove(game_window, 1, 10);
        drawEnergyBar(BBB.showStamina()); // opponent stamina

	wmove(game_window, 15, 43);
	whline(game_window, ' ', 25);
	wmove(game_window, 15, 43);
	drawEnergyBar(AAA.showStamina()); // my stamina

        // draw static string to hold percentage
        mvwprintw(game_window, 2, 1, " - O P P O N E N T   S T A M I N A -      //");
	mvwprintw(game_window, 3, 1, "-----------------------------------------//");
	mvwprintw(game_window, 16, 33, "\\\\        -   MY  J A G U M O N   -");
	mvwprintw(game_window, 17, 34, "\\\\-----------------------------------------"); 

        // draw ENEMY percentage
        wattron(game_window, A_BOLD);
        if(BBB.showStamina() <= 25) {
          wattron(game_window, COLOR_PAIR(4));
          if(tick % 100 < 50)
            mvwprintw(game_window, 2, 38, "%i%%", BBB.showStamina()); 
          wattroff(game_window, COLOR_PAIR(4));
        } else
            mvwprintw(game_window, 2, 38, "%i%%", BBB.showStamina()); 
        wattroff(game_window, A_BOLD);

	// draw MY stamina percentage
	wattron(game_window, A_BOLD);
        if(AAA.showStamina() <= 25) {
          wattron(game_window, COLOR_PAIR(4));
          if(tick % 100 < 50)
            mvwprintw(game_window, 16, 37, "%i%%", AAA.showStamina()); 
          wattroff(game_window, COLOR_PAIR(4));
        } else
            mvwprintw(game_window, 16, 37, "%i%%", AAA.showStamina()); 
        wattroff(game_window, A_BOLD);

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
                    exit_flag = false;
                    break;
                }

                else if(in_char == 'q') {
                    exit_flag = true;
                    break;
                }

                wrefresh(game_window);

                tick++;
                usleep(10000); // 1 ms
            }
        }

        if(exit_flag) break;

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

        wattron(game_window, COLOR_PAIR(col_pair));
        wattron(game_window, A_BOLD);
        waddch(game_window, '/');
        wattroff(game_window, A_BOLD);
        wattroff(game_window, COLOR_PAIR(col_pair));
    }
}

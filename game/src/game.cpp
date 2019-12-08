#include <unistd.h>
#include <ncurses.h>

#include <cstdint>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <random>

#include "game.h"
#include "JagumonData.h"

WINDOW* main_window;
WINDOW* game_window;

rect game_area;
rect screen_area;

vec2ui cur_size;

void Attack(Jagumon&, Jagumon&);
void Defense(Jagumon&, Jagumon&);
void actingBySpeed(Jagumon&, Jagumon&, char);

size_t story_part = 0;  	// manage story diaglog lines
size_t story_position = 0; 	// manage story dialog sections
int tick = 0; 			// manage time in game


const std::vector<std::string> battle_text = { 
        "Your Jagumon attacked the opponent Jagumon! Hell yeah!", 
        "Opponent Jagumon attacked your Jagumon. It hurts!",
        "Your Jagumon healed itself. Nice to see the work-life balance!", 
        "Opponent Jagumon healed itself. Let's show them what we've got!",
        "Oh noooo!!! Your Jagumon fainted!",
        "Aha! Opponent's Jagumon is down! Way to go!",
	"Let's go! Another Jagumon!!",
	"Here comes another opponent Jagumon!",
	"YAY! You've won the battle! JeoGyeo is crying!!!",
	"Damn! You've lost... Let's try again later T^T"
};

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
    
    int choo_char = 0; // selecting Jagumon in CHOOSE JAGUMON PHASE
    int in_char = 0; // selecting action in BATTLE PHASE
    int finger = 0; // point at the Jagumon of Player's choice
    int blockComp1 = -1;
    int blockComp2 = -1;
    int blockComp3 = -1;
    int blockComp4 = -1;
    int blockComp5 = -1;
    int fingerComp = 0;  // point at the Jaugmon of Comp's choice
    int deadPC = 0; // Count down how many PC jagumons are dead
    bool exit_flag = false; // when True, immediately finish the game

    int party = 0; 	// n-th place in player's party. Starts at 0 because
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
    //size_t story_part = 0;
    //size_t story_position = 0;

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
		else finger=9;
		break;
	    case 'd':
		if(finger<9) finger++;
		else finger=0;
		break;
	    case 'q':
		exit_flag = true;
		break;
	    case ' ':
                if(party == 3) {
                  party++;
                  break;
                }
                if(finger == 0) {
                  User[party] = AAA;
                }
                else if(finger == 1) {
                  User[party] = BBB;
                }
                else if(finger == 2) {
                  User[party] = CCC;
                }
                else if(finger == 3) {
                  User[party] = DDD;
                }
                else if(finger == 4) {
                  User[party] = EEE;
                }
                else if(finger == 5) {
                  User[party] = GGG;
                }
                else if(finger == 6) {
                  User[party] = HHH;
                }
                else if(finger == 7) {
                  User[party] = JJJ;
                }
                else if(finger == 8) {
                  User[party] = KKK;
                }
                else if(finger == 9) {
                  User[party] = LLL;
                }
                if(party==0) blockComp1=finger;
                else if(party==1) blockComp2=finger;
                else if(party==2) blockComp3=finger;

                //randomize computer's option, avoid chosen one's
                do {
                  fingerComp = rand()%10;
                } while(fingerComp == blockComp1 or fingerComp == blockComp2 or fingerComp == blockComp3 or fingerComp == blockComp4 or fingerComp == blockComp5);
                if(fingerComp == 0) {
                  PC[party] = AAA;
                }
                else if(fingerComp == 1) {
                  PC[party] = BBB;
                }
                else if(fingerComp == 2) {
                  PC[party] = CCC;
                }
                else if(fingerComp == 3) {
                  PC[party] = DDD;
                }
                else if(fingerComp == 4) {
                  PC[party] = EEE;
                }
                else if(fingerComp == 5) {
                  PC[party] = GGG;
                }
                else if(fingerComp == 6) {
                  PC[party] = HHH;
                }
                else if(fingerComp == 7) {
                  PC[party] = JJJ;
                }
                else if(fingerComp == 8) {
                  PC[party] = KKK;
                }
                else if(fingerComp == 9) {
                  PC[party] = LLL;
                }
                if(party == 0) blockComp4=fingerComp;
                else if(party ==1) blockComp5=fingerComp;
		party++;
		break;
	    default:
		break;
	}
        
        // print out UI
        /*
	for(int i=0; i<10; i++) {
          mvwprintw(game_window, 2+i, 10, jagumon[i].showName());
	}
        */
       
        mvwprintw(game_window, 2, 10, "AAA");
        mvwprintw(game_window, 3, 10, "BBB");
        mvwprintw(game_window, 4, 10, "CCC");
        mvwprintw(game_window, 5, 10, "DDD");
        mvwprintw(game_window, 6, 10, "EEE");
        mvwprintw(game_window, 7, 10, "GGG");
        mvwprintw(game_window, 8, 10, "HHH");
        mvwprintw(game_window, 9, 10, "JJJ");
        mvwprintw(game_window, 10, 10, "KKK");
        mvwprintw(game_window, 11, 10, "LLL");

	mvwprintw(game_window, 2+finger, 9, ">");
        mvwprintw(game_window, 14, 9, "User Jagumon:");
        mvwprintw(game_window, 14, 25, "PC Jagumon:");
        if(party >= 1) {
          mvwprintw(game_window, 17, 9, "3. ");
          mvwprintw(game_window, 17, 12, User[0].showName());
          mvwprintw(game_window, 15, 25, "1. ");
          mvwprintw(game_window, 15, 28, PC[0].showName());
          if(party >=2) {
            mvwprintw(game_window, 16, 9, "2. ");
            mvwprintw(game_window, 16, 12, User[1].showName());
            mvwprintw(game_window, 16, 25, "2. ");
            mvwprintw(game_window, 16, 28, PC[1].showName());
          }
          if(party >=3) {
            mvwprintw(game_window, 15, 9, "1. ");
            mvwprintw(game_window, 15, 12, User[2].showName());
            mvwprintw(game_window, 17, 25, "3. ");
            mvwprintw(game_window, 17, 28, PC[2].showName());
          }
        }
        /*
        if(party >= 3) {
          for(int i=2; i>=0; i--) {
            mvwprintw(game_window, 17-i, 9, User[i].showName());
          }
        }
        */

	// refresh windows
	wrefresh(main_window);
	wrefresh(game_window);

	if(exit_flag or party == 4) break;
	

	tick++;
	
	usleep(10000); //1ms
    }

    // ----------- BATTLE PHASE -----------
    tick = 0;
    Jagumon presentUser = User.back();
    Jagumon presentPC = PC.front();
    story_part = 0;
    story_position = 0;
    while(1) {

	// TODO check if Jagumons are alive. If not, gameover.
        // clear game window
        werase(game_window);
	// read input, set them all to lower case
        in_char = wgetch(main_window);
        in_char = tolower(in_char);

        switch(in_char) { 
	    case 'd':
                actingBySpeed(presentUser, presentPC, 'd');
		break;
	    case 'a':
                actingBySpeed(presentUser, presentPC, 'a');
	        break;
	    case 'q':
                exit_flag = true; 
                break;
            case ' ':
                break;
            default: 
                break;
        }


        // draw UI elements
        // energy bar
        wmove(game_window, 1, 10);
        whline(game_window, ' ', 25); // health bar is 25 chars long
        wmove(game_window, 1, 10);
        drawEnergyBar(presentPC.showStamina()); // opponent stamina

	wmove(game_window, 15, 43);
	whline(game_window, ' ', 25);
	wmove(game_window, 15, 43);
	drawEnergyBar(presentUser.showStamina()); // my stamina

        // draw static string to hold percentage
        mvwprintw(game_window, 2, 1, " - O P P O N E N T   S T A M I N A -      //");
	mvwprintw(game_window, 3, 1, "-----------------------------------------//");
	mvwprintw(game_window, 16, 33, "\\\\        -   MY  J A G U M O N   -");
	mvwprintw(game_window, 17, 34, "\\\\-----------------------------------------"); 
    
        // Jagumons appearance
        mvwprintw(game_window, 16, 10, presentUser.showName());
        mvwprintw(game_window, 2, 60, presentPC.showName());

        // draw ENEMY percentage
        wattron(game_window, A_BOLD);
        if(presentPC.showStamina() <= 25) {
          wattron(game_window, COLOR_PAIR(4));
          if(tick % 100 < 50)
            mvwprintw(game_window, 2, 38, "%i%%", presentPC.showStamina()); 
          wattroff(game_window, COLOR_PAIR(4));
        } else
            mvwprintw(game_window, 2, 38, "%i%%", presentPC.showStamina()); 
        wattroff(game_window, A_BOLD);

	// draw MY stamina percentage
	wattron(game_window, A_BOLD);
        if(presentUser.showStamina() <= 25) {
          wattron(game_window, COLOR_PAIR(4));
          if(tick % 100 < 50)
            mvwprintw(game_window, 16, 37, "%i%%", presentUser.showStamina()); 
          wattroff(game_window, COLOR_PAIR(4));
        } else
            mvwprintw(game_window, 16, 37, "%i%%", presentUser.showStamina()); 
        wattroff(game_window, A_BOLD);

        // usleep(100);

        // refresh windows
        wrefresh(main_window);
        wrefresh(game_window);
	    
	if(presentUser.showStamina() == 0) {
	  User.pop_back();
          if(User.size() == 0) {
	    story_position = 0;
            //werase(main_window);
            while(story_position < battle_text[9].length()) {
              wattron(main_window, A_BOLD);
              mvwaddch(main_window, 20, 5 + story_position, battle_text[9][story_position]);
              wattroff(main_window, A_BOLD);
              story_position++;
              usleep(10000);
              wrefresh(main_window);
	    }
            sleep(3);
            exit_flag=true;
            break;
	  }
          else if(User.size() > 0 and User.size() <= 3 and exit_flag==false) {
            presentUser = User.back();
	    story_position = 0;
            //werase(main_window);
            while(story_position < battle_text[6].length()) {
              wattron(main_window, A_BOLD);
              mvwaddch(main_window, 20, 5 + story_position, battle_text[6][story_position]);
              wattroff(main_window, A_BOLD);
              story_position++;
              usleep(10000);
              wrefresh(main_window);
	    }
            sleep(2);
          }
          mvwhline(main_window, 20, 1, ' ', screen_area.width() - 2);
	}
	if(presentPC.showStamina() == 0) {
	  deadPC++;
          if(deadPC == 3) {
	    story_position = 0;
            //werase(main_window);
            while(story_position < battle_text[8].length()) {
              wattron(main_window, A_BOLD);
              mvwaddch(main_window, 20, 5 + story_position, battle_text[8][story_position]);
              wattroff(main_window, A_BOLD);
              story_position++;
              usleep(10000);
              wrefresh(main_window);
	    }
            sleep(3);
            exit_flag=true;
            break;
	  }
          else if(deadPC >= 0 and deadPC < 3) {
            presentPC = PC[deadPC];
	    story_position = 0;
            //werase(main_window);
            while(story_position < battle_text[7].length()) {
              wattron(main_window, A_BOLD);
              mvwaddch(main_window, 20, 5 + story_position, battle_text[7][story_position]);
              wattroff(main_window, A_BOLD);
              story_position++;
              usleep(10000);
              wrefresh(main_window);
	    }
            sleep(2);
          }
          mvwhline(main_window, 20, 1, ' ', screen_area.width() - 2);
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

void Attack(Jagumon &user, Jagumon &other) {
  if(user.showPower() >= other.showStamina()) {
    other.setStamina(0);
  }
  else {
    other.setStamina(other.showStamina() - user.showPower());
  }
}

void Defense(Jagumon &user, Jagumon &other) {
  if(user.showStamina() + user.showDefense() <= 130)
    user.setStamina(user.showStamina() + user.showDefense());
  else
    user.setStamina(130);
}

void actingBySpeed(Jagumon &player, Jagumon &opponent, char choice) {
  srand(time(NULL));
  opponentRand = rand() % 2;
  if(opponent.showStamina() >= 100) opponentRand = 0;

  if (choice == 'a') {
    if(player.showSpeed() >= opponent.showSpeed()) {
      Attack(player, opponent);
      story_position = 0;
      //werase(main_window);
      while(story_position < battle_text[0].length()) {
        wattron(main_window, A_BOLD);
        mvwaddch(main_window, 20, 5 + story_position, battle_text[0][story_position]);
        wattroff(main_window, A_BOLD);
        story_position++;
        usleep(10000);
        wrefresh(main_window);
      }
      sleep(2);
      mvwhline(main_window, 20, 1, ' ', screen_area.width() - 2);

      if(opponent.showStamina() > 0) {
        if(opponentRand == 0) {
          Attack(opponent, player);
	  story_position = 0;
	  //werase(main_window);
          while(story_position < battle_text[1].length()) {
            wattron(main_window, A_BOLD);
            mvwaddch(main_window, 20, 5 + story_position, battle_text[1][story_position]);
            wattroff(main_window, A_BOLD);
            story_position++;
            usleep(10000);
            wrefresh(main_window);
          }
          sleep(2);
          mvwhline(main_window, 20, 1, ' ', screen_area.width() - 2);
          if(player.showStamina() == 0) {
            story_position = 0;
            //werase(main_window);
            while(story_position < battle_text[4].length()) {
              wattron(main_window, A_BOLD);
              mvwaddch(main_window, 20, 5 + story_position, battle_text[4][story_position]);
              wattroff(main_window, A_BOLD);
              story_position++;
              usleep(10000);
              wrefresh(main_window);
            }
            sleep(2);
            mvwhline(main_window, 20, 1, ' ', screen_area.width() - 2);
          }
        }
        else {
          Defense(opponent, player);
	  story_position = 0;
          //werase(main_window);
          while(story_position < battle_text[3].length()) {
            wattron(main_window, A_BOLD);
            mvwaddch(main_window, 20, 5 + story_position, battle_text[3][story_position]);
            wattroff(main_window, A_BOLD);
            story_position++;
            usleep(10000);
            wrefresh(main_window);
          }
          sleep(2);
          mvwhline(main_window, 20, 1, ' ', screen_area.width() - 2);
        }  
      }
      else if(opponent.showStamina() == 0) {
        story_position = 0;
        //werase(main_window);
	while(story_position < battle_text[5].length()) {
          wattron(main_window, A_BOLD);
          mvwaddch(main_window, 20, 5 + story_position, battle_text[5][story_position]);
          wattroff(main_window, A_BOLD);
          story_position++;
          usleep(10000);
          wrefresh(main_window);
        }
        sleep(2);
        mvwhline(main_window, 20, 1, ' ', screen_area.width() - 2);
      }
    }
    else if(player.showSpeed() < opponent.showSpeed()) {
      if(opponentRand == 0) {
        Attack(opponent, player);
	story_position = 0;
        //werase(main_window);
        while(story_position < battle_text[1].length()) {
          wattron(main_window, A_BOLD);
          mvwaddch(main_window, 20, 5 + story_position, battle_text[1][story_position]);
          wattroff(main_window, A_BOLD);
          story_position++;
          usleep(10000);
          wrefresh(main_window);
        }
        sleep(2);
        mvwhline(main_window, 20, 1, ' ', screen_area.width() - 2);
      }
      else {
        Defense(opponent, player);
	story_position = 0;
        //werase(main_window);
        while(story_position < battle_text[3].length()) {
          wattron(main_window, A_BOLD);
          mvwaddch(main_window, 20, 5 + story_position, battle_text[3][story_position]);
          wattroff(main_window, A_BOLD);
          story_position++;
          usleep(10000);
          wrefresh(main_window);
        }
        sleep(2);
        mvwhline(main_window, 20, 1, ' ', screen_area.width() - 2);
      }
      if(player.showStamina() > 0) {
        Attack(player, opponent);
        story_position = 0;
        //werase(main_window);
        while(story_position < battle_text[0].length()) {
          wattron(main_window, A_BOLD);
          mvwaddch(main_window, 20, 5 + story_position, battle_text[0][story_position]);
          wattroff(main_window, A_BOLD);
          story_position++;
          usleep(10000);
          wrefresh(main_window);
        }
        sleep(2);
        mvwhline(main_window, 20, 1, ' ', screen_area.width() - 2);
        if(opponent.showStamina() == 0) {
          story_position = 0;
          //werase(main_window);
	  while(story_position < battle_text[5].length()) {
            wattron(main_window, A_BOLD);
            mvwaddch(main_window, 20, 5 + story_position, battle_text[5][story_position]);
            wattroff(main_window, A_BOLD);
            story_position++;
            usleep(10000);
            wrefresh(main_window);
          }
          sleep(2);
          mvwhline(main_window, 20, 1, ' ', screen_area.width() - 2);
        }
      }
      else if(player.showStamina() == 0) {
        story_position = 0;
        //werase(main_window);
        while(story_position < battle_text[4].length()) {
          wattron(main_window, A_BOLD);
          mvwaddch(main_window, 20, 5 + story_position, battle_text[4][story_position]);
          wattroff(main_window, A_BOLD);
          story_position++;
          usleep(10000);
          wrefresh(main_window);
        }
        sleep(2);
        mvwhline(main_window, 20, 1, ' ', screen_area.width() - 2);
      }
    }
  }
  else if(choice == 'd') {
    if(player.showSpeed() >= opponent.showSpeed()) {
      Defense(player, opponent);
      story_position = 0;
      //werase(main_window);
      while(story_position < battle_text[2].length()) {
        wattron(main_window, A_BOLD);
        mvwaddch(main_window, 20, 5 + story_position, battle_text[2][story_position]);
        wattroff(main_window, A_BOLD);
        story_position++;
        usleep(10000);
        wrefresh(main_window);
      }
      sleep(2);
      mvwhline(main_window, 20, 1, ' ', screen_area.width() - 2);
      if(opponentRand == 0) {
        Attack(opponent, player);
	story_position = 0;
        //werase(main_window);
        while(story_position < battle_text[1].length()) {
          wattron(main_window, A_BOLD);
          mvwaddch(main_window, 20, 5 + story_position, battle_text[1][story_position]);
          wattroff(main_window, A_BOLD);
          story_position++;
          usleep(10000);
          wrefresh(main_window);
        }
        sleep(2);
        mvwhline(main_window, 20, 1, ' ', screen_area.width() - 2);
	if(player.showStamina() == 0) {
	  story_position = 0;
          //werase(main_window);
          while(story_position < battle_text[4].length()) {
            wattron(main_window, A_BOLD);
            mvwaddch(main_window, 20, 5 + story_position, battle_text[4][story_position]);
            wattroff(main_window, A_BOLD);
            story_position++;
            usleep(10000);
            wrefresh(main_window);
          }
          sleep(2);
          mvwhline(main_window, 20, 1, ' ', screen_area.width() - 2);
	}
      }
      else {
        Defense(opponent, player);
	story_position = 0;
        //werase(main_window);
        while(story_position < battle_text[3].length()) {
          wattron(main_window, A_BOLD);
          mvwaddch(main_window, 20, 5 + story_position, battle_text[3][story_position]);
          wattroff(main_window, A_BOLD);
          story_position++;
          usleep(10000);
          wrefresh(main_window);
        }
        sleep(2);
        mvwhline(main_window, 20, 1, ' ', screen_area.width() - 2);
      }
    }
    else if(player.showSpeed() < opponent.showSpeed()) {
      if(opponentRand == 0) {
        Attack(opponent, player);
	story_position = 0;
        //werase(main_window);
        while(story_position < battle_text[1].length()) {
          wattron(main_window, A_BOLD);
          mvwaddch(main_window, 20, 5 + story_position, battle_text[1][story_position]);
          wattroff(main_window, A_BOLD);
          story_position++;
          usleep(10000);
          wrefresh(main_window);
        }
        sleep(2);
        mvwhline(main_window, 20, 1, ' ', screen_area.width() - 2);
	if(player.showStamina() == 0) {
	  story_position = 0;
          //werase(main_window);
          while(story_position < battle_text[4].length()) {
            wattron(main_window, A_BOLD);
            mvwaddch(main_window, 20, 5 + story_position, battle_text[4][story_position]);
            wattroff(main_window, A_BOLD);
            story_position++;
            usleep(10000);
            wrefresh(main_window);
          }
          sleep(2);
          mvwhline(main_window, 20, 1, ' ', screen_area.width() - 2);
	}
      }
      else {
        Defense(opponent, player);
	story_position = 0;
        //werase(main_window);
        while(story_position < battle_text[3].length()) {
          wattron(main_window, A_BOLD);
          mvwaddch(main_window, 20, 5 + story_position, battle_text[3][story_position]);
          wattroff(main_window, A_BOLD);
          story_position++;
          usleep(10000);
          wrefresh(main_window);
        }
        sleep(2);
        mvwhline(main_window, 20, 1, ' ', screen_area.width() - 2);
      }
      if(player.showStamina() > 0) {
        Defense(player, opponent);
        story_position = 0;
        //werase(main_window);
        while(story_position < battle_text[2].length()) {
          wattron(main_window, A_BOLD);
          mvwaddch(main_window, 20, 5 + story_position, battle_text[2][story_position]);
          wattroff(main_window, A_BOLD);
          story_position++;
          usleep(10000);
          wrefresh(main_window);
        }
        sleep(2);
        mvwhline(main_window, 20, 1, ' ', screen_area.width() - 2);
      }
    }
  }
}

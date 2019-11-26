#include <ncurses.h>
#include <unistd.h>

void drawBorders(WINDOW* screen);
void updateScreenSize();

int main(int argc, char *argv[]) {
  int parent_x, parent_y;
  int new_x, new_y;
  int score_size = 3;
  int game_not_finished = 1;
  initscr();
  noecho();
  curs_set(FALSE);
  
  // get our maximum window dimensions 
  getmaxyx(stdscr, parent_y, parent_x);
  
  // set up initial windows 
  WINDOW *field = newwin(parent_y - score_size, parent_x, 0, 0); 
  WINDOW *score = newwin(score_size, parent_x, parent_y - score_size, 0); // draw to our windows 
  mvwprintw(field, 0, 0, "Field");
  mvwprintw(score, 0, 0, "Score");
  
  // draw borders
  drawBorders(field);
  drawBorders(score);
  
  while(game_not_finished) {
    // continuously get window size
    getmaxyx(stdscr, new_y, new_x);
    // change border size when the screen size changes
    if(new_y!=parent_y || new_x!=parent_x) {
      // get new window size
      parent_x = new_x;
      parent_y = new_y;
      // resize both field window and score window
      wresize(field, new_y - score_size, new_x);
      wresize(score, score_size, new_x);
      // move the score window according to the new screen size
      mvwin(score, new_y - score_size, 0);
      // clean all screen
      wclear(stdscr);
      wclear(field);
      wclear(score);
      // visualize the boarder
      draw_borders(field);
      draw_borders(score);
    }
    
    // draw in our windows
    mvwprintw(field, 1, 1, "Field");
    mvwprintw(score, 1, 1, "Score");

    // refresh each window
    wrefresh(field);
    wrefresh(score);
    sleep(5);
    game_not_finished = 0;
    refresh();
  }
  
  // clean up
  delwin(field);
  delwin(score);
  endwin(); 

  return 0;
}

void drawBorders(WINDOW* screen) {
  int x, y, i;
  getmaxyx(screen, y, x);
  
  // 4 corners
  mvwprintw(screen, 0, 0, "+");
  mvwprintw(screen, y-1, 0, "+");
  mvwprintw(screen, 0, x-1, "+");
  mvwprintw(screen, y-1, x-1, "+");

  // sides
  for(i=1; i < (y-1); i++) {
    mvwprintw(screen, i, 0, "|");
    mvwprintw(screen, i, x-1, "|");
  }
  // top and bottom
  for(i=1; i < (x-1); i++) {
    mvwprintw(screen, 0, i,  "-");
    mvwprintw(screen, y-1, i, "-");
  }
}

void updateScreenSize() {

}





































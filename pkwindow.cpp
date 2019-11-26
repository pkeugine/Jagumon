#include <ncurses.h>
#include <unistd.h>

#define DELAY 30000

int main(int argc, char *argv[]) {
  int x = 0, y = 0;
  int max_y = 0, max_x = 0;
  int next_x = 0;
  int direction = 1;

  initscr();
  noecho();
  curs_set(FALSE);

  while(1) {
    getmaxyx(stdscr, max_y, max_x); // Get the current screen size
    clear(); // Clear the screen of all
    // previously-printed characters
    mvprintw(y, x, "o"); // Print our "ball" at the current xy position
    refresh();

    usleep(DELAY); // Shorter delay between movements
    next_x = x + direction; // Advance the ball to the right

    if (next_x >= max_x || next_x < 0) {
      direction*= -1;
    } else {
      x+= direction;
    }
  }

  endwin();
}

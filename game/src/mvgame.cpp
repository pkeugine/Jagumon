#include <unistd.h>
#include <ncurses.h>

#include <cstdint>
#include <string>

#include "game.h"

struct {
  vec2i pos;
  char disp_char;
} player;

WINDOW* window;

int init() {
  window = initscr();
  cbreak();
  noecho();
  clear();
  refresh();

  // enable function keys
  keypad(window, true);

  // disable input blocking
  nodelay(window, true);

  // hide cursor
  curs_set(0);

  if(!has_colors()) {
      endwin();
      printf("ERROR: Terminal does not support color.\n");
      exit(1);
  }

  // enable color modification
  start_color();

  // draw box around screen
  attron(A_BOLD);
  box(window, 0, 0);
  attroff(A_BOLD);

  return 0;
}


void run() {

  player.disp_char = '0';
  player.pos = {10, 5};

  int in_char;

  bool exit_requested = false;

  while(1) {
    in_char = wgetch(window);

    mvaddch(player.pos.y, player.pos.x, ' ');

    switch(in_char) {
      case 'q':
        exit_requested = true;
        break;
      case KEY_UP:
      case 'w':
        player.pos.y -= 1;
        break;
      case KEY_DOWN:
      case 's':
        player.pos.y += 1;
        break;
      case KEY_LEFT:
      case 'a':
        player.pos.x -= 1;
        break;
      case KEY_RIGHT:
      case 'd':
        player.pos.x += 1;
        break;
      default:
        break;
    }

    mvaddch(player.pos.y, player.pos.x, player.disp_char);

    if(exit_requested) break;

    //100 ms wait
//    usleep(100000);

    refresh();
  }
}


void close() {
  endwin();
}

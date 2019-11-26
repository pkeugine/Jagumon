#include <ncurses.h>

int main(int argc, char * argv[]){
  char ch;
  initscr();
  keypad(stdscr, TRUE);
  noecho();
  
  printw("Hi There!!!\n");
  ch = getch();
  mvprintw(20, 20, "%c", ch);
  refresh();
  attron(A_BOLD);
  printw("%c", ch);
  getch();

  return 0;
}

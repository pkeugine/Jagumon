#include <ncurses.h>

int main(){
  int ch;
  
  initscr(); // start curses mode
  raw();  // line buffering disabled
  keypad(stdscr, TRUE); // we get F1, F2, ... etc
  noecho(); // don't echo() while we do getch

  printw("Type any character to see it in bold\n");
  ch = getch();
  // if raw() hadn't been called we have to
  // press enter before it gets to the program

  if(ch==KEY_F(1)) // without keypad enabled this will not get to us
    printw("F1 key pressed"); // without noecho() some ugly escape characters would appear
  else{
    printw("The pressed key is ");
    attron(A_BOLD);
    printw("%c", ch);
    attroff(A_BOLD);
  }
  refresh();
  printw("dkdkdkdk");
  getch();
  printw("aaaaaaaaaaaaaaa");    
  refresh();
  endwin();
  return 0;
}

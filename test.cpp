#include <fcntl.h>
#include <ncurses.h>
#include <iostream>

void mainScreen() {
    WINDOW *win;
    WINDOW *win2;
    initscr();
    start_color();

    int location = 18;

    init_pair(1, COLOR_WHITE, COLOR_YELLOW);
    init_pair(2, COLOR_YELLOW, COLOR_WHITE);

    refresh();

    win = newwin(17, 80, 0, 0);
    win2 = newwin(7, 80, 17, 0);

    wbkgd(win, COLOR_PAIR(1));
    wbkgd(win2, COLOR_PAIR(2));

    attron(COLOR_PAIR(1));
    mvwprintw(win, 9, 28, "WELCOME TO JAGUMON!");
    attroff(COLOR_PAIR(1));

    wattron(win2, COLOR_PAIR(2));
    mvwprintw(win2, 3, 18, "GET START");
    mvwprintw(win2, 3, 48, "EXIT");
    wattroff(win2, COLOR_PAIR(2));
    wmove(win2, 3, location);

    wrefresh(win);
    wrefresh(win2);

    keypad(stdscr, TRUE);
    noecho();
    curs_set(1);

    /* when push EXIT button
    delwin(win);
    delwin(win2);

    endwin();
    */
    while (1) {
        int input = getch();

        if (input == KEY_RIGHT) {
            location += 30;
            if (location == 18) { // GET START
                wattron(win2, COLOR_PAIR(2));
                mvwprintw(win2, 3, 48, "EXIT");
                wattroff(win2, COLOR_PAIR(2));

                wattron(win2, COLOR_PAIR(1));
                mvwprintw(win2, 3, location, "GET START");
                wattroff(win2, COLOR_PAIR(1));
            } else  {
                location == 48; // EXIT
                wattron(win2, COLOR_PAIR(2));
                mvwprintw(win2, 3, 18, "GET START");
                wattroff(win2, COLOR_PAIR(2));

                wattron(win2, COLOR_PAIR(1));
                mvwprintw(win2, 3, location, "EXIT");
                wattroff(win2, COLOR_PAIR(1));
            }
        } else if (input == KEY_LEFT) {
            location -= 30;
            if (location == 18) {
                wattron(win2, COLOR_PAIR(2));
                mvwprintw(win2, 3, 48, "EXIT");
                wattroff(win2, COLOR_PAIR(2));

                wattron(win2, COLOR_PAIR(1));
                mvwprintw(win2, 3, location, "GET START");
                wattroff(win2, COLOR_PAIR(1));
            } else  { // EXIT
                location == 48;
                wattron(win2, COLOR_PAIR(2));
                mvwprintw(win2, 3, 18, "GET START");
                wattroff(win2, COLOR_PAIR(2));

                wattron(win2, COLOR_PAIR(1));
                mvwprintw(win2, 3, location, "EXIT");
                wattroff(win2, COLOR_PAIR(1));
            }
        }
    }
    wrefresh(win);
    wrefresh(win2);
}

int main() { mainScreen(); }

#include "pcre.h"
#include <ncurses.h>
#include <locale.h>

#define DX 3
#define ONLELINE 3
#define MAXSTR 80

void main() {
    setlocale(LC_ALL, "");
    WINDOW *winA, *winB, *winO;
    char inA[MAXSTR], inB[MAXSTR];
    int c = 0;
    int half;

    initscr();
    cbreak();
    printw("Input:");
    refresh();

    half = (COLS-2*DX)/2;
    winA = newwin(ONLELINE, half, DX, DX);
    winB = newwin(ONLELINE, half, DX, DX+half);
    winO = newwin(LINES-ONLELINE-DX*2, (COLS-2*DX), DX+ONLELINE, DX);
    keypad(winA, TRUE);
    keypad(winB, TRUE);
    scrollok (winO, TRUE);
    wmove(winO, 1, 0);
    do {
        werase(winA);
        box(winA, 0, 0);
        wrefresh(winA);
        werase(winB);
        box(winB, 0, 0);
        wrefresh(winB);
        mvwgetnstr(winA, 1, 1, inA, MAXSTR);
        mvwgetnstr(winB, 1, 1, inB, MAXSTR);
        char *res = pattern_match(inA, inB);

        wprintw(winO, res);
        free(res);
        box(winO, 0, 0);
        wrefresh(winO);
    } while(*inA);

    endwin();

}



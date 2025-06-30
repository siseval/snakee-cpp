#include "curspp.h"

void init_curses()
{
    setlocale(LC_ALL, "");

    initscr();
    timeout(0);
    nocbreak();
    noecho();
    curs_set(0);

    start_color();
    use_default_colors();

    init_pair(1, COLOR_BLACK, -1);
    init_pair(2, COLOR_RED, -1);
    init_pair(3, COLOR_GREEN, -1);
    init_pair(4, COLOR_YELLOW, -1);
    init_pair(5, COLOR_BLUE, -1);
    init_pair(6, COLOR_MAGENTA, -1);
    init_pair(7, COLOR_WHITE, -1);
}

void end_curses()
{
    endwin();
}

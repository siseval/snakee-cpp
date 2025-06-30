#ifndef CURSPP_H
#define CURSPP_H

#include <string>
#include <curses.h>
#include <locale>
#include <cstdint>


namespace curspp {

enum direction
{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT
};
using direction = enum direction;

enum color
{
    BLACK = 1,
    RED = 2,
    GREEN = 3,
    YELLOW = 4,
    BLUE = 5,
    MAGENTA = 6,
    WHITE = 7,
};
using color = enum color;

using vec2i = std::pair<int16_t, int16_t>;
using vec2f = std::pair<float, float>;

void init_curses();
void end_curses();

inline void draw_pixel(const vec2i pos, const std::string pixel)
{
    mvaddstr(pos.second, pos.first, pixel.data());
}

inline void set_color(const enum color c)
{
    attron(COLOR_PAIR(c));
}

inline void set_bold(const bool enable)
{
    if (enable)
    {
        attron(A_BOLD);
    }
    else
    {
        attroff(A_BOLD);
    }
}

inline vec2i get_screen_size()
{
    int16_t width, height;
    getmaxyx(stdscr, height, width);
    return { width, height };
}

inline vec2i get_cursor_pos()
{
    int16_t x, y;
    getyx(stdscr, y, x);
    return { x, y };
}

inline void set_timeout_ms(int16_t ms)
{
    timeout(ms);
}

inline void clear_screen()
{
    erase();
}

}
#endif // CURSPP_H

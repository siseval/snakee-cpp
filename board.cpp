#include "board.h"

namespace snakee
{

bool screen_size_changed(vec2::vec2s &prev_screen_size)
{
    vec2::vec2s current_screen_size = curspp::get_screen_size();
    if (current_screen_size.x != prev_screen_size.x || current_screen_size.y != prev_screen_size.y)
    {
        prev_screen_size = current_screen_size;
        return true;
    }
    return false;
}

void update_board(struct board &board)
{
    const vec2::vec2s screen_size = curspp::get_screen_size();
    board.board_size = screen_size * vec2::vec2d { 0.4, 0.8 };
    board.board_origin = screen_size / vec2::vec2b { 4, 2 } - board.board_size / 2;
}

}

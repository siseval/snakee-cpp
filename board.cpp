#include "board.h"

namespace snakee
{

static vec2::vec2s get_food_pos(const vec2::vec2s board_size)
{
    return vec2::vec2s{
        static_cast<int16_t>(std::rand() % board_size.x),
        static_cast<int16_t>(std::rand() % board_size.y)
    };
}

bool is_in_bounds(const vec2::vec2s pos, const vec2::vec2s board_size)
{
    return pos.x >= 0 && pos.x < board_size.x && pos.y >= 0 && pos.y < board_size.y;
}

bool pos_has_food(const vec2::vec2s pos, const std::unordered_set<vec2::vec2s> &food_positions)
{
    return food_positions.find(pos) != food_positions.end();
}

void spawn_food(const std::unique_ptr<struct board> &board)
{
    board->food_positions.insert(get_food_pos(board->size));
}

bool screen_size_changed(vec2::vec2s &prev_screen_size)
{
    const vec2::vec2s current_screen_size = curspp::get_screen_size();
    if (current_screen_size != prev_screen_size)
    {
        prev_screen_size = current_screen_size;
        return true;
    }
    return false;
}

void update_board(const std::unique_ptr<struct board> &board)
{
    const vec2::vec2s screen_size = curspp::get_screen_size();
    board->size = screen_size * vec2::vec2d{ BOARD_TO_SCREEN_RATIO / 2, BOARD_TO_SCREEN_RATIO };
    board->screen_origin = screen_size / 2 - board->size / vec2::vec2s{ 1, 2 };

    std::vector<vec2::vec2s> to_erase;
    for (vec2::vec2s food_pos : board->food_positions)
    {
        if (is_in_bounds(food_pos, board->size))
        {
            continue;
        }
        to_erase.push_back(food_pos);
    }
    for (const auto &pos : to_erase)
    {
        board->food_positions.erase(pos);
        spawn_food(board);
    }
}

}

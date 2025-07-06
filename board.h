#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
#include <vector>
#include <unordered_set>
#include "curspp/vec2.h"
#include "curspp/curspp.h"

namespace snakee
{

constexpr double BOARD_TO_SCREEN_RATIO = 0.5;

struct board
{
    vec2::Vec2<int16_t> size;
    vec2::Vec2<int16_t> screen_origin;
    std::unordered_set<vec2::Vec2<int16_t>> food_positions;
};

bool is_in_bounds(const vec2::Vec2<int16_t> pos, const vec2::Vec2<int16_t> board_size);
void spawn_food(const std::unique_ptr<struct board> &board);
bool pos_has_food(const vec2::Vec2<int16_t> pos, const std::unordered_set<vec2::Vec2<int16_t>> &food_positions);
bool screen_size_changed(vec2::Vec2<int16_t> &prev_screen_size);
void update_board(const std::unique_ptr<struct board> &board);

}

#include "curspp/curspp.h"

#endif // BOARD_H

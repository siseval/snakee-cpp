#ifndef DRAW_H
#define DRAW_H

#include <cstdint>
#include <vector>
#include <unordered_set>
#include "curspp/curspp.h"
#include "curspp/vec2.h"

namespace snakee
{

constexpr curspp::color SNAKE_HEAD_COLOR = curspp::WHITE;
constexpr curspp::color SNAKE_BODY_COLOR = curspp::WHITE;
constexpr curspp::color SNAKE_DEAD_COLOR = curspp::RED;
constexpr curspp::color FOOD_COLOR = curspp::YELLOW;
constexpr curspp::color BORDER_COLOR = curspp::WHITE;

const std::string SNAKE_HEAD_CHAR = "▩";
const std::string SNAKE_BODY_CHAR = "▨";
const std::string BORDER_CHARS[7] = {"╭", "─", "╮", "│", "╰", "─", "╯"};
const std::string FOOD_CHAR = "▣";


inline vec2::Vec2<int16_t> game_to_screen_pos(const vec2::Vec2<int16_t> game_pos, const vec2::Vec2<int16_t> board_origin)
{
    return board_origin + game_pos * vec2::Vec2<int16_t>{ 2, 1 };
}

void draw_snake(const vec2::Vec2<int16_t> origin, const std::vector<vec2::Vec2<int16_t>> &body_segments, bool dead = false);
void draw_border(const vec2::Vec2<int16_t> origin, const vec2::Vec2<int16_t> border_size);
void draw_food(const vec2::Vec2<int16_t> origin, const std::unordered_set<vec2::Vec2<int16_t>> &food_positions);
void draw_stats(const vec2::Vec2<int16_t> origin, const int64_t timer, const int32_t score);

}

#endif // DRAW_H

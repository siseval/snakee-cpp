#ifndef DRAW_H
#define DRAW_H

#include <cstdint>
#include <vector>
#include "curspp/curspp.h"
#include "curspp/vec2.h"

namespace snakee
{

const std::string snake_head_char = "▨";
const std::string snake_body_char = "▨";
const std::string border_chars[7] = {"╭", "─", "╮", "│", "╰", "─", "╯"};


inline vec2::vec2s board_to_screen_pos(const vec2::vec2s game_pos, const vec2::vec2s board_origin)
{
    return board_origin + game_pos * vec2::vec2s{ 2, 1 };
}

void draw_snake(const vec2::vec2s origin, const std::vector<vec2::vec2s> body_segments);
void draw_border(vec2::vec2s board_origin, vec2::vec2s board_size);

}

#endif // DRAW_H

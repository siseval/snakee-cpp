#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <cstdint>
#include <vector>
#include "curspp/curspp.h"
#include "curspp/vec2.h"

namespace snakee
{

struct snake
{
    std::vector<vec2::Vec2<int16_t>> body_segments;
    vec2::Vec2<int16_t> cur_direction;
};

void handle_input(vec2::Vec2<int16_t> &direction);
void increase_snake_length(const std::unique_ptr<struct snake> &snake, const int16_t increase);
void handle_movement(const std::unique_ptr<struct snake> &snake);
bool should_move(const int16_t tick_ms, int64_t &last_tick);

}

#endif // MOVEMENT_H

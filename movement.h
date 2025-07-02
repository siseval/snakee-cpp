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
    std::vector<vec2::vec2s> body_segments;
    vec2::vec2s cur_direction;
};

void handle_input(vec2::vec2s &direction);
void increase_snake_length(struct snake &snake, const int16_t increase);
void handle_movement(const int16_t tick_ms, int64_t &last_tick, struct snake &snake);

}

#endif // MOVEMENT_H

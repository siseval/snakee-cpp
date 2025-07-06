#include "movement.h"

namespace snakee
{

static vec2::vec2s direction_to_segment(vec2::vec2s from, vec2::vec2s to)
{
    if (to.y < from.y)
    {
        return curspp::UP;
    }
    else if (to.y > from.y)
    {
        return curspp::DOWN;
    }
    else if (to.x < from.x)
    {
        return curspp::LEFT;
    }
    else if (to.x > from.x)
    {
        return curspp::RIGHT;
    }
    return vec2::vec2s::zero();
}

 bool should_move(const int16_t tick_ms, int64_t &last_tick)
{
    const int64_t current_time = std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::system_clock::now().time_since_epoch()).count();

    if (current_time - last_tick >= tick_ms)
    {
        last_tick = current_time;
        return true;
    }
    return false;
}

void handle_movement(const std::unique_ptr<struct snake> &snake)
{
    for (int16_t i = snake->body_segments.size(); i > 0; --i)
    {
        vec2::vec2s move_direction = 
            direction_to_segment(snake->body_segments[i], snake->body_segments[i - 1]);

        snake->body_segments[i] = snake->body_segments[i] + move_direction;
    }
    snake->body_segments[0] = snake->body_segments[0] + snake->cur_direction;
}

void increase_snake_length(const std::unique_ptr<struct snake> &snake, const int16_t increase)
{
    for (int16_t i = 0; i < increase; ++i)
    {
        snake->body_segments.push_back(snake->body_segments.back());
    }
}

void handle_input(vec2::vec2s &direction)
{
    const char input = curspp::get_input();
    vec2::vec2s new_direction = direction;
    switch (input)
    {
        case 'k':
            new_direction = curspp::UP;
            break;
        case 'j':
            new_direction = curspp::DOWN;
            break;
        case 'h':
            new_direction = curspp::LEFT;
            break;
        case 'l':
            new_direction = curspp::RIGHT;
            break;
    }
    if (new_direction == -direction)
    {
        return;
    }
    direction = new_direction;
    curspp::flush_input();
}

}

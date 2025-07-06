#include "draw.h"

namespace snakee
{

void draw_snake(const vec2::vec2s origin, const std::vector<vec2::vec2s> &body_segments, bool dead)
{
    curspp::set_color(dead ? SNAKE_DEAD_COLOR : SNAKE_HEAD_COLOR);
    curspp::add_str(game_to_screen_pos(body_segments[0], origin), SNAKE_HEAD_CHAR.data());
    curspp::set_color(dead ? SNAKE_DEAD_COLOR : SNAKE_BODY_COLOR);
    for (size_t i = 1; i < body_segments.size(); ++i)
    {
        const vec2::vec2s &segment = body_segments[i];
        const vec2::vec2s segment_screen_pos = game_to_screen_pos(segment, origin);
        curspp::add_str(segment_screen_pos, SNAKE_BODY_CHAR.data());
    }
}

void draw_border(const vec2::vec2s origin, const vec2::vec2s border_size)
{
    const vec2::vec2s top_left = game_to_screen_pos(vec2::vec2s{ -1, -1 }, origin);
    const vec2::vec2s bottom_right = game_to_screen_pos(vec2::vec2s::zero() + border_size, origin);

    for (int16_t y = top_left.y; y <= bottom_right.y; ++y)
    {
        curspp::add_str({ top_left.x, y }, BORDER_CHARS[3].data());
        curspp::add_str({ bottom_right.x, y }, BORDER_CHARS[3].data());
    }
    for (int16_t x = top_left.x; x <= bottom_right.x; ++x)
    {
        curspp::add_str({ x, top_left.y }, BORDER_CHARS[1].data());
        curspp::add_str({ x, bottom_right.y }, BORDER_CHARS[5].data());
    }
    curspp::add_str(top_left, BORDER_CHARS[0].data());
    curspp::add_str({ bottom_right.x, top_left.y }, BORDER_CHARS[2].data());
    curspp::add_str(bottom_right, BORDER_CHARS[6].data());
    curspp::add_str({ top_left.x, bottom_right.y }, BORDER_CHARS[4].data());
}

void draw_food(const vec2::vec2s origin, const std::unordered_set<vec2::vec2s> &food_positions)
{
    curspp::set_color(FOOD_COLOR);
    for (const auto food_pos : food_positions)
    {
        const vec2::vec2s food_screen_pos = game_to_screen_pos(food_pos, origin);
        curspp::add_str(food_screen_pos, FOOD_CHAR.data());
    }
}

void draw_stats(const vec2::vec2s origin, const int64_t timer, const int32_t score)
{
    curspp::set_color(curspp::WHITE);
    const std::string score_text = "Score: " + std::to_string(score);
    const std::string timer_text = "Time: " + std::to_string(timer) + "s";
    
    curspp::add_str(origin + vec2::vec2s{ 0, -1 }, score_text.data());
}

}

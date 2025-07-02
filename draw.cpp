#include "draw.h"

namespace snakee
{

void draw_snake(const vec2::vec2s origin, const std::vector<vec2::vec2s> body_segments)
{
    curspp::set_color(curspp::YELLOW);
    vec2::vec2s head_screen_pos = board_to_screen_pos(body_segments[0], origin);
    curspp::draw_pixel(head_screen_pos, snake_head_char.data());

    curspp::set_color(curspp::WHITE);
    for (int16_t i = 0; i < body_segments.size(); ++i)
    {
        const vec2::vec2s &segment = body_segments[i];
        const vec2::vec2s segment_screen_pos = board_to_screen_pos(segment, origin);
        curspp::draw_pixel(segment_screen_pos, snake_body_char.data());
    }
}

void draw_border(vec2::vec2s board_origin, vec2::vec2s board_size)
{
    const int16_t top_y = board_origin.y;
    const int16_t bot_y = board_origin.x + board_size.y - 1;
    const int16_t left_x = board_origin.x;
    const int16_t right_x = (board_origin.x + board_size.x + 1) * 2;

    curspp::set_color(curspp::WHITE);
    curspp::draw_pixel({ left_x, top_y }, border_chars[0].data());
    curspp::draw_pixel({ left_x, bot_y }, border_chars[4].data());
    for (int16_t i = 1; i <= right_x - left_x; ++i)
    {
         curspp::draw_pixel({ static_cast<int16_t>(left_x + i), top_y }, border_chars[1].data());
         curspp::draw_pixel({ static_cast<int16_t>(left_x + i), bot_y }, border_chars[5].data());
    }
    curspp::draw_pixel({ static_cast<int16_t>(right_x + 1), top_y  }, border_chars[2].data());
    curspp::draw_pixel({ static_cast<int16_t>(right_x + 1), bot_y  }, border_chars[6].data());
    for (int16_t i = 1; i < bot_y - top_y; ++i)
    {
         curspp::draw_pixel({ left_x, static_cast<int16_t>(top_y + i) }, border_chars[3].data());
         curspp::draw_pixel({ static_cast<int16_t>(right_x + 1), static_cast<int16_t>(top_y + i) }, border_chars[3].data());
    }
}

}

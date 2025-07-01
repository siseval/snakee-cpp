#include "snakee.h"

const std::string snake_head_char = "▨";
const std::string snake_body_char = "▨";
const std::string border_chars[7] = {"╭", "─", "╮", "│", "╰", "─", "╯"};

struct snake
{
    std::vector<vec2::vec2s> body_segments;
    vec2::vec2s cur_direction;
};

struct board
{
    vec2::vec2s board_dimensions;
    vec2::vec2s board_origin;
};

namespace snakee {

static inline vec2::vec2s board_to_screen_pos(const vec2::vec2s game_pos, const vec2::vec2s board_origin)
{
    return board_origin + game_pos * vec2::vec2s{ 2, 1 };
}


static void draw_border(struct board board)
{
    const int16_t top_y = board.board_origin.y;
    const int16_t bot_y = board.board_origin.x + board.board_dimensions.y - 1;
    const int16_t left_x = board.board_origin.x;
    const int16_t right_x = (board.board_origin.x + board.board_dimensions.x + 1) * 2;

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

static void draw_snake(const vec2::vec2s origin, const struct snake snake)
{
    curspp::set_color(curspp::YELLOW);
    vec2::vec2s head_screen_pos = board_to_screen_pos(snake.body_segments[0], origin);
    curspp::draw_pixel(head_screen_pos, snake_head_char.data());

    curspp::set_color(curspp::WHITE);
    for (int16_t i = 0; i < snake.body_segments.size(); ++i)
    {
        const vec2::vec2s &segment = snake.body_segments[i];
        const vec2::vec2s segment_screen_pos = board_to_screen_pos(segment, origin);
        curspp::draw_pixel(segment_screen_pos, snake_body_char.data());
    }
}

static void handle_input(vec2::vec2s &direction)
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
}

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

static bool should_move(const int16_t tick_ms, int64_t &last_tick)
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

static void handle_movement(const int16_t tick_ms, int64_t &last_tick, struct snake &snake)
{
    if (should_move(tick_ms, last_tick))
    {
        handle_input(snake.cur_direction);
        for (int16_t i = snake.body_segments.size(); i > 0; --i)
        {
            vec2::vec2s move_direction = 
                direction_to_segment(snake.body_segments[i], snake.body_segments[i - 1]);

            snake.body_segments[i] = snake.body_segments[i] + move_direction;
        }
        snake.body_segments[0] = snake.body_segments[0] + snake.cur_direction;
    }
}

static void update_board(struct board &board)
{
    const vec2::vec2s screen_size = curspp::get_screen_size();
    board.board_dimensions =
        { 
            static_cast<int16_t>(std::round(screen_size.x * 0.4f)),
            static_cast<int16_t>(std::round(screen_size.y * 0.8f))
        };
    board.board_origin =
        { 
            static_cast<int16_t>(std::round(screen_size.x / 4 - board.board_dimensions.x / 2)),
            static_cast<int16_t>(std::round(screen_size.y / 2 - board.board_dimensions.y / 2))
        };
}

static void increase_snake_length(struct snake &snake, const int16_t increase)
{
    for (int16_t i = 0; i < increase; ++i)
    {
        snake.body_segments.push_back(snake.body_segments.back());
    }
}

static void main_loop()
{
    struct board board;
    update_board(board);
    struct snake snake = 
        {
            .body_segments = 
            { { 
                static_cast<int16_t>(board.board_dimensions.x / 2),
                static_cast<int16_t>(board.board_dimensions.y / 2)
            } },
            .cur_direction = curspp::RIGHT,
        };

    increase_snake_length(snake, 2);

    int16_t tick_ms = 150;
    int64_t last_tick = std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::system_clock::now().time_since_epoch()).count();

    bool running = true;
    while (running)
    {
        update_board(board);
        curspp::clear_screen();
        handle_movement(tick_ms, last_tick, snake);
        draw_border(board);
        draw_snake(board.board_origin, snake);
    }
}

void snake_start_game()
{
    main_loop();
}

void snake_main_menu()
{
    const std::string title = "-= SNAKEE =-";
    const std::vector<std::string> buttons =
        {
            ":: Play ::",
            ":: AI ::",
            ":: Quit ::"
        };

    const vec2::vec2s screen_size = curspp::get_screen_size();

    curspp::set_bold(true);
    const int8_t menu_height_offset = -2;
    int8_t selection = 0;
    bool has_selected = false;
    while (!has_selected)
    {
        curspp::set_color(curspp::WHITE);
        const vec2::vec2s title_pos = 
            { 
                static_cast<int16_t>(screen_size.x / 2 - title.length() / 2), 
                static_cast<int16_t>(menu_height_offset + screen_size.y / 2 - (buttons.size() * 3 / 2)) 
            };
        curspp::draw_pixel(title_pos, title.data());

        for (int8_t i = 0; i < buttons.size(); ++i)
        {
            curspp::set_color(selection == i ? curspp::YELLOW : curspp::WHITE);
            const vec2::vec2s button_pos =
                { 
                    static_cast<int16_t>(screen_size.x / 2 - buttons[i].length() / 2),
                    static_cast<int16_t>(menu_height_offset + screen_size.y / 2 + i * 3 + (i == buttons.size() - 1 ? 1 : 0))
                };
            curspp::draw_pixel(button_pos, buttons[i].data());
        }

        const char input = curspp::get_input();
        switch (input)
        {
            case 'k':
                selection = (selection - 1) % buttons.size();
                break;
            case 'j':
                selection = (selection + 1) % buttons.size();
                break;
            case 'f':
                has_selected = true;
                break;
        }

        if (has_selected)
        {
            switch (selection)
            {
                case 0:
                    has_selected = false;
                    snake_start_game();
                    return;
                case 1:
                    break;
                case 2:
                    return;
            }
        }
    }
}


}

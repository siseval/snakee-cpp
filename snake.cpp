#include "snake.h"

const std::string snake_char = "O";
const std::string border_chars[7] = {"╭", "─", "╮", "│", "╰", "─", "╯"};

namespace snake {

static void draw_border(const curspp::vec2i board_dimensions, const curspp::vec2i center)
{
    const int16_t top_y = center.second - board_dimensions.second / 2;
    const int16_t bot_y = center.second + board_dimensions.second / 2;
    const int16_t left_x = center.first - board_dimensions.first / 2;
    const int16_t right_x = center.first + board_dimensions.first / 2;

    curspp::set_color(curspp::WHITE);
    curspp::draw_pixel({ left_x, top_y }, border_chars[0].data());
    curspp::draw_pixel({ left_x, bot_y }, border_chars[4].data());

    for (int16_t i = 1; i <= right_x - left_x; ++i)
    {
         curspp::draw_pixel({ left_x + i, top_y }, border_chars[1].data());
         curspp::draw_pixel({ left_x + i, bot_y }, border_chars[5].data());
    }
    curspp::draw_pixel({ right_x + 1, top_y  }, border_chars[2].data());
    curspp::draw_pixel({ right_x + 1, bot_y  }, border_chars[6].data());
    for (int16_t i = 1; i < bot_y - top_y; ++i)
    {
         curspp::draw_pixel({ left_x, top_y + i }, border_chars[3].data());
         curspp::draw_pixel({ right_x + 1, top_y + i }, border_chars[3].data());
    }
}

static void draw_snake(const curspp::vec2i origin, const std::vector<curspp::vec2i> snake_body)
{
    for (int16_t i = 0; i < snake_body.size(); ++i)
    {
        const curspp::vec2i &segment = snake_body[i];
        const curspp::vec2i segment_screen_pos =
            {
                origin.first + segment.first,
                origin.second + segment.second
            };
        if (i == 0)
        {
            curspp::set_color(curspp::YELLOW);
        }
        else
        {
            curspp::set_color(curspp::WHITE);
        }
        curspp::draw_pixel(segment_screen_pos, snake_char.data());
    }
}

static void handle_input(curspp::direction &direction)
{
    const char input = getch();
    switch (input)
    {
        case 'k':
            direction = curspp::UP;
            break;
        case 'j':
            direction = curspp::DOWN;
            break;
        case 'h':
            direction = curspp::LEFT;
            break;
        case 'l':
            direction = curspp::RIGHT;
            break;
    }
}

static void move_snake(std::vector<curspp::vec2i> snake_body, const curspp::direction direction)
{
    switch (direction)
    {
        case curspp::UP:
            snake_body[0].second--;
            break;
        case curspp::DOWN:
            snake_body[0].second++;
            break;
        case curspp::LEFT:
            snake_body[0].first--;
            break;
        case curspp::RIGHT:
            snake_body[0].first++;
            break;
    }
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

static void main_loop()
{
    const curspp::vec2i screen_size = curspp::get_screen_size();

    const curspp::vec2i board_dimensions = 
        { 
            screen_size.first *0.8f, 
            screen_size.second * 0.8f 
        };
    const curspp::vec2i screen_center = 
        { 
            screen_size.first / 2, 
            screen_size.second / 2 
        };
    const curspp::vec2i board_origin = 
        { 
            screen_center.first - board_dimensions.first / 2, 
            screen_center.second - board_dimensions.second / 2 
        };

    const std::vector<curspp::vec2i> snake_body;

    curspp::direction cur_direction = curspp::RIGHT;
    int16_t snake_length = 1;

    int16_t tick_ms = 150;
    int64_t last_tick = std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::system_clock::now().time_since_epoch()).count();

    bool running = true;
    while (running)
    {
        handle_input(cur_direction);
        curspp::clear_screen();
        if (should_move(tick_ms, last_tick))
        {
            move_snake(snake_body, cur_direction);
        }
        draw_border(board_dimensions, screen_center);
        draw_snake(board_origin, snake_body);
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

    const curspp::vec2i screen_size = curspp::get_screen_size();

    attron(A_BOLD);
    const int8_t menu_height_offset = -2;
    int8_t selection = 0;
    bool has_selected = false;
    while (!has_selected)
    {
        curspp::set_color(curspp::WHITE);
        const curspp::vec2i title_pos = 
            { 
                screen_size.first / 2 - title.length() / 2, 
                menu_height_offset + screen_size.second / 2 - (buttons.size() * 3 / 2) 
            };
        curspp::draw_pixel(title_pos, title.data());

        for (int8_t i = 0; i < buttons.size(); ++i)
        {
            curspp::set_color(selection == i ? curspp::YELLOW : curspp::WHITE);
            const curspp::vec2i button_pos =
                { 
                    screen_size.first / 2 - buttons[i].length() / 2,
                    menu_height_offset + screen_size.second / 2 + i * 3 + (i == buttons.size() - 1 ? 1 : 0)
                };
            curspp::draw_pixel(button_pos, buttons[i].data());
        }

        const char input = getch();
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

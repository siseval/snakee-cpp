#include "snakee.h"


namespace snakee {


static void main_loop(struct board &board, struct snake &snake)
{
    int16_t tick_ms = 150;
    int64_t last_tick = std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::system_clock::now().time_since_epoch()).count();

    vec2::vec2s screen_size = curspp::get_screen_size();
    bool running = true;
    while (running)
    {
        if (screen_size_changed(screen_size))
        {
            update_board(board);
        }
        handle_movement(tick_ms, last_tick, snake);
        curspp::clear_screen();
        draw_border(board.board_origin, board.board_size);
        draw_snake(board.board_origin, snake.body_segments);
    }
}

void snake_start_game()
{
    struct board board;
    update_board(board);
    struct snake snake = 
        {
            .body_segments = { board.board_size / 2 },
            .cur_direction = curspp::RIGHT,
        };
    increase_snake_length(snake, 8);

    main_loop(board, snake);
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

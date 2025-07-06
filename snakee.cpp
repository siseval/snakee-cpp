#include "snakee.h"


namespace snakee {

static inline int64_t get_current_time_ms()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
}

static inline void update_timer(int64_t &timer, const int64_t start_time)
{
    timer = (get_current_time_ms() - start_time) / 1000;
}

static void handle_food(const std::unique_ptr<struct snake> &snake, const std::unique_ptr<struct board> &board, struct stats &stats)
{
    if (pos_has_food(snake->body_segments[0], board->food_positions))
    {
        board->food_positions.erase(snake->body_segments[0]);
        spawn_food(board);
        increase_snake_length(snake, 1);
        stats.score += POINTS_PER_FOOD;
    }
}


static bool should_die(std::vector<vec2::vec2s> &body_segments, vec2::vec2s board_size)
{
    if (std::find(body_segments.begin() + 1, body_segments.end(), body_segments[0]) != body_segments.end())
    {
        return true;
    }
    if (!is_in_bounds(body_segments[0], board_size))
    {
        return true;
    }
    return false;
}

static void main_loop(const std::unique_ptr<struct board> &board, const std::unique_ptr<struct snake> &snake, struct stats &stats)
{
    int16_t tick_ms = 150;
    int64_t last_tick = get_current_time_ms();
    int64_t start_time = last_tick;

    vec2::vec2s screen_size = curspp::get_screen_size();
    bool running = true;

    spawn_food(board);
    while (running)
    {
        update_timer(stats.timer_sec, start_time);
        if (screen_size_changed(screen_size))
        {
            update_board(board);
        }
        if (!should_move(tick_ms, last_tick))
        {
            continue;
        }

        handle_food(snake, board, stats);
        handle_input(snake->cur_direction);
        handle_movement(snake);
        if (should_die(snake->body_segments, board->size))
        {
            running = false;
        }

        curspp::clear_screen();
        draw_border(board->screen_origin, board->size);
        draw_food(board->screen_origin, board->food_positions);
        draw_snake(board->screen_origin, snake->body_segments, !running);
        draw_stats(board->screen_origin, stats.timer_sec, stats.score);
    }

    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    snake_end_menu(stats, board);
}

void snake_start_game()
{
    auto board = std::make_unique<struct board>();
    update_board(board);

    auto snake = std::make_unique<struct snake>();
    snake->body_segments = { board->size / 2 },
    snake->cur_direction = curspp::RIGHT;

    struct stats stats = { 0, 0 };

    main_loop(board, snake, stats);
}

static void do_menu(const std::vector<std::string> &buttons, int8_t &selection, const vec2::vec2s &screen_size, int8_t menu_height_offset, const std::string &title = "", const int8_t button_gap = 2)
{
    bool has_selected = false;
    while (!has_selected)
    {
        curspp::set_color(curspp::WHITE);
        const vec2::vec2s title_pos = 
            { 
                static_cast<int16_t>(screen_size.x / 2 - title.length() / 2), 
                static_cast<int16_t>(menu_height_offset + screen_size.y / 2 - (buttons.size() * 3 / 2)) 
            };
        curspp::add_str(title_pos, title.data());

        for (int8_t i = 0; i < buttons.size(); ++i)
        {
            curspp::set_color(selection == i ? curspp::YELLOW : curspp::WHITE);
            const vec2::vec2s button_pos =
                { 
                    static_cast<int16_t>(screen_size.x / 2 - buttons[i].length() / 2),
                    static_cast<int16_t>(menu_height_offset + screen_size.y / 2 + i * button_gap + (i == buttons.size() - 1 ? 0 : 0))
                };
            curspp::add_str(button_pos, buttons[i].data());
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
    }
}

void snake_main_menu()
{
    curspp::clear_screen();

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
    do_menu(buttons, selection, screen_size, menu_height_offset, title, 3);

    switch (selection)
    {
        case 0:
            snake_start_game();
            return;
        case 1:
            break;
        case 2:
            return;
    }
}

void snake_end_menu(struct stats stats, const std::unique_ptr<struct board> &board)
{
    curspp::set_color(curspp::WHITE);
    bool selected = false;
    while (!selected)
    {
        curspp::clear_screen();
        update_board(board);
        draw_border(board->screen_origin, board->size);
        const vec2::vec2s center = curspp::get_screen_size() / 2;
        constexpr int stats_height_offset = -6;

        const std::string title = "-= GAME  OVER =-";
        const std::string score_text = "Score: " + std::to_string(stats.score);
        const std::string timer_text = "Time: " + std::to_string(stats.timer_sec) + "s";

        vec2::vec2s title_pos = center + vec2::vec2s{ 0, stats_height_offset } - vec2::vec2s{ static_cast<int16_t>(title.length() / 2), 0 };
        vec2::vec2s score_pos = center + vec2::vec2s{ static_cast<int16_t>(-(score_text.length() / 2)), stats_height_offset + 3 };
        vec2::vec2s timer_pos = center + vec2::vec2s{ static_cast<int16_t>(-(timer_text.length() / 2)), stats_height_offset + 5 };

        curspp::add_str(title_pos, title.data());
        curspp::add_str(score_pos, score_text.data());
        curspp::add_str(timer_pos, timer_text.data());

        const std::vector<std::string> buttons =
        {
            ":: Play Again ::",
            ":: Main Menu ::",
            ":: Quit ::"
        };
        int8_t selection = 0;
        do_menu(buttons, selection, curspp::get_screen_size(), 3, "", 2);
        
        switch (selection)
        {
            case 0:
                snake_start_game();
                return;
            case 1:
                snake_main_menu();
                return;
            case 2:
                selected = true;
                break;
        }
    }
}

}

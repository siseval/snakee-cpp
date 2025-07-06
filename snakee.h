#ifndef SNAKE_H
#define SNAKE_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <thread>
#include <memory>

#include "curspp/curspp.h"
#include "curspp/vec2.h"
#include "board.h"
#include "movement.h"
#include "draw.h"

namespace snakee 
{

constexpr int32_t POINTS_PER_FOOD = 1;

struct stats
{
    int32_t score;
    std::int64_t timer_sec;
};

void snake_end_menu(struct stats stats, const std::unique_ptr<struct board> &board);
void snake_main_menu();
void snake_start_game();

}


#endif

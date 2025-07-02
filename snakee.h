#ifndef SNAKE_H
#define SNAKE_H

#include <cstdint>
#include <vector>
#include <chrono>

#include "curspp/curspp.h"
#include "curspp/vec2.h"
#include "board.h"
#include "movement.h"
#include "draw.h"

namespace snakee 
{

void snake_main_menu();
void snake_start_game();

}


#endif

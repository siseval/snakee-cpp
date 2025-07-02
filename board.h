#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
#include "curspp/vec2.h"
#include "curspp/curspp.h"

namespace snakee
{

struct board
{
    vec2::vec2s board_size;
    vec2::vec2s board_origin;
};

bool screen_size_changed(vec2::vec2s &prev_screen_size);
void update_board(struct board &board);

}

#include "curspp/curspp.h"

#endif // BOARD_H

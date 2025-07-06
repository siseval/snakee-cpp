#include "snakee.h"

int32_t main()
{
    std::srand(time(NULL));
    curspp::init();
    snakee::snake_start_game();
    curspp::end();
}

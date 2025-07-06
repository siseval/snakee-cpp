#include "snakee.h"

int32_t main()
{
    std::srand(time(NULL));
    curspp::init();
    snakee::snake_main_menu();
    curspp::end();
}

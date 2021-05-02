#include "./include/splashkit/splashkit.h"
#include "player.h"
#include "power_up.h"
#include "menu.h"
#include "lost_in_space.h"
#include "heads_up_display.h"
#include "music_player.h"


int main()
{
    open_window("Lost In Space", 800, 800);
    load_resources();

    handle_menu();

    return 0;
}
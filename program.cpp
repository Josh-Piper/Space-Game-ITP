#include "splashkit.h"
#include "./Source/GameData/lost_in_space.h"
#include "./Source/MenuData/menu_logic.h"

int main()
{
    load_resources();
    window w = open_window("Lost In Space", 800, 800);
    window_set_icon(w, bitmap_named("icon"));

    handle_menu();
    return 0;
}
#include "splashkit.h"
#include "./Source/GameData/lost_in_space.h"
#include "./Source/MenuData/menu_logic.h"

int main()
{
    open_window("Lost In Space", 800, 800);
    load_resources();

    handle_menu();

    return 0;
}
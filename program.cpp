#include "splashkit.h"
#include "./Source/GameData/lost_in_space.h"
#include "./Source/MenuData/menu_logic.h"

/**
 * The program contains the following features:
 * 1.) Home Screen Menu 
 * 2.) Settings Menu - Manipulate music player settings
 * 3.) Information Menu - Open user's default browser to the repo depending on OS
 * 4.) Leaderboard Menu - Allows Sorting for the Leaderboard Entries and Has File I/O Validation 
 * 5.) Pause Screen
 * 6.) End Screen (Allows insert leaderboard entry)
 * 7.) Levelling System - Changes what Enemies Spawn in and Percentage of Spawn Rates for Power Ups
 * 8.) Enemies to Start Spawning past Level 2, these enemies navigate towards the user 
 */

int main()
{
    load_resources();
    window w = open_window("Lost In Space", 800, 800);
    window_set_icon(w, bitmap_named("icon"));

    handle_menu();
    return 0;
}
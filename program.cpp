#include "./include/splashkit/splashkit.h"
#include "player.h"
#include "power_up.h"
#include "heads_up_display.h"

/**
 * Load the game images, sounds, etc.
 */

using std::to_string;

void load_resources()
{
    load_resource_bundle("game_bundle", "lost_in_space.txt");
}

/**
 * Entry point.
 * 
 * Manages the initialisation of data, the event loop, and quitting.
 */
int main()
{
    open_window("Lost In Space", 800, 800);
    load_resources();

    player_data player;
    power_up_data power_up;

    player = new_player();
    power_up = new_power_up(550, 550);

    while ( ! quit_requested() )
    {
        // Handle input to adjust player movement
        process_events();
        handle_input(player);

        // Perform movement and update the camera
        update_player(player);
        update_power_up(power_up);

        draw_heads_up_display(player);
        // as well as the player who can move
        draw_player(player);
        draw_power_up(power_up);

        refresh_screen(60);
    }

    return 0;
}
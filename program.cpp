#include "./include/splashkit/splashkit.h"
#include "player.h"
#include "power_up.h"
#include "lost_in_space.h"
#include "heads_up_display.h"

/**
 * Load the game images, sounds, etc.
 */

using std::to_string;


/**
 * Entry point.
 * 
 * Manages the initialisation of data, the event loop, and quitting.
 */
int main()
{
    open_window("Lost In Space", 800, 800);
    load_resources();
    
    game_data game { new_game() };

    while ( ! quit_requested() )
    {
        process_events();

        handle_input(game.player);
        update_game(game);
        draw_game(game);
    }

    return 0;
}
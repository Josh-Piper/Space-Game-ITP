#include "splashkit.h"
#include "lost_in_space.h"
#include "heads_up_display.h"
#include "player.h"
#include "menu.h"
#include "power_up.h"
#include <vector>

using std::vector;
const int MINIMUM_SPACE_LOCATION = -1500;
const int MAXIMUM_SPACE_LOCATION = 1500;

void load_resources()
{
    load_resource_bundle("game_bundle", "lost_in_space.txt");
}

game_data new_game()
{
    game_data game;
    game.player = new_player();
    game.game_timer = create_timer("GameTimer");
    start_timer(game.game_timer);
    return game;
}


void draw_power_ups(const vector<power_up_data> &powerups)
{
    for (int i = 0; i < powerups.size(); i++)
    {
        draw_power_up(powerups[i]);
    }
}

void add_power_up(game_data &game)
{
    int x = rnd(MINIMUM_SPACE_LOCATION, MAXIMUM_SPACE_LOCATION);
    int y = rnd(MINIMUM_SPACE_LOCATION, MAXIMUM_SPACE_LOCATION);
    power_up_data result = new_power_up(x, y);
    game.power_ups.push_back( result );
}

void update_power_ups(vector<power_up_data> power_ups) //cannot be const
{
    for (int i; i < power_ups.size(); i++)
        update_power_up(power_ups[i]);
}

void apply_power_up(game_data  &game, power_up_kind kind)
{
    if (kind == FUEL)
    {
        game.player.fuel_pct *=  1.25;
        if (game.player.fuel_pct >= 1.0)
            game.player.fuel_pct = 1.0;
        
    } 
    else if (kind == SHIELD)
    {
        game.player.power_up_counter = 1.0;
    }
    else if (kind == POTION && game.player.power_up_counter == 0.0)
    {
        game.player.fuel_pct -= 0.15;
    }
    else if (kind == DROPS)
    {
        game.player.score += 5;
    }
    else if (kind == DIAMOND)
    {
        game.player.score += 50;
    } 
    else //kind == COIN
    {   
        game.player.score += 1;
    }

    game.player.total_power_ups += 1;
    game.player.current_power_up = power_up_bitmap(kind);
}

void remove_power_up(game_data &game, int index)
{
    game.power_ups[index] = game.power_ups[game.power_ups.size() - 1];
    game.power_ups.pop_back();
}

void check_collisions(game_data &game) //causes segmentations faults
{
    for (int index = game.power_ups.size() - 1; index >= 0; index--)
    {
        if (sprite_collision(game.player.player_sprite, game.power_ups[index].power_up_sprite))
        {
            play_sound_effect("pop");
            apply_power_up(game, game.power_ups[index].kind);
            remove_power_up(game, index);
        }
    }
}

void update_game(game_data &game)
{
    
    // Perform movement and update the camera
    if (rnd(0, 1000) <= 30)
        add_power_up(game);

    check_collisions(game);

    update_player(game.player);
    update_power_ups(game.power_ups);

}

void draw_game(const game_data &game)
{
    draw_heads_up_display(game);

    draw_power_ups(game.power_ups);
    draw_player(game.player);

    refresh_screen(60);
}

void handle_game_paused(menu_handler_data &global_menu_handler)
{
    if (key_typed(ESCAPE_KEY))
        {
            bool exit_menu;
            do 
            {
                process_events();
                // Exit the game (go back to the menu screens) when the user clicks home in paused_screen_menu
                exit_menu = paused_screen_menu(global_menu_handler);
            } while ( ! exit_menu && ! quit_requested() );
        }
}

game_state handle_game()
{
    menu_handler_data global_menu_handler = create_menu_handler();
    global_menu_handler.game_state = PLAY_GAME_SCREEN;
    game_data game { new_game() };

    while ( ! quit_requested() )
    {
        process_events();

        // Handle the looping of the game itself
        handle_input(game.player);
        update_game(game);
        draw_game(game);


        // When the user types the escape key, handle the in-game paused menu
        handle_game_paused(global_menu_handler);

        // Exit the game when not in playing game mode
        if (global_menu_handler.game_state != PLAY_GAME_SCREEN) break;
        
    }

    // If user wants to return the home screen. Then return it
    if (global_menu_handler.game_state == HOME_SCREEN) return HOME_SCREEN;
    return END_GAME;
}


#include "splashkit.h"
#include "lost_in_space.h"
#include "heads_up_display.h"
#include "player.h"
#include "../../Source/MenuData/menu_logic.h"
#include "power_up.h"
#include "lost_in_space_drawing.h"
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
    game.game_level = 1;
    game.game_timer = create_timer("GameTimer");
    game.level_up_timer_cooldown = create_timer("CoolDownTimer");
    start_timer(game.game_timer);
    return game;
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
        game.player.fuel_pct +=  0.20;
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

void check_collisions(game_data &game) 
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

int get_power_up_occurence_limitation(const game_data &game)
{
    int result;
    switch (game.game_level)
    {
        case 1: result = 30; break;
        case 2: result = 28; break;
        case 3: result = 26; break;
        case 4: result = 24; break;
        case 5: result = 22; break;
        case 6: result = 18; break;
        case 7: result = 15; break;
        case 8: result = 13; break;
        case 9: result = 10; break;
        default: result = 5; break;
    }
    return result;
}

void update_level_per_minute(game_data &game)
{
    // Change level every 10 seconds CURRENT
    double game_timer_in_seconds = (timer_ticks(game.game_timer) / 1000.0); // Convert milliseconds to seconds
    double game_level_per_10_secs = game.game_level * 5;  // Change to 60 to make per 60 seconds
    double draw_next_level_cooldown = (timer_ticks(game.level_up_timer_cooldown) / 1000.0);
    //write_line("Game Level per 10 Seconds: " + to_string(game_level_per_10_secs) + "\nGame Timer Minutes: " + to_string(game_timer_in_seconds) + "\n");
    if (game_timer_in_seconds >= game_level_per_10_secs) 
    {
        game.game_level++;
        game.power_ups.clear(); // reset powerups
        start_timer( game.level_up_timer_cooldown ); // Draw the next level information
    }

    if (draw_next_level_cooldown > 3.0) // if the draw next level has drawn for longer than 3 seconds
    {
        reset_timer(game.level_up_timer_cooldown);
        stop_timer(game.level_up_timer_cooldown);
    }
}

void update_level(game_data &game)
{
    // Normal Level
    if (game.game_level % 5 != 0)
    {
        update_level_per_minute(game);
    }
    // Boss Level - every 5 
    else 
    {
        // do nothing
    }  
}

void update_game(game_data &game)
{   
    int power_up_occurence_limitation = get_power_up_occurence_limitation(game);

    // Check for the level of the game here
    update_level(game);


    // Add enemies for level 2, 


    // Have stuff pop up 



    
    // Perform movement and update the camera
    if (rnd(0, 1000) <= power_up_occurence_limitation)
        add_power_up(game);

    check_collisions(game);

    update_player(game.player);
    update_power_ups(game.power_ups);
}

void handle_game_paused(menu_handler_data &global_menu_handler, game_data &game)
{
    if (key_typed(ESCAPE_KEY))
        {
            bool exit_menu;
            do 
            {
                process_events();
                // Exit the game (go back to the menu screens) when the user clicks home in paused_screen_menu
                exit_menu = handle_paused_screen_menu(global_menu_handler, game);
            } while ( ! exit_menu && ! quit_requested() );
        }
}

void handle_end_game(menu_handler_data &global_menu_handler, game_data &game)
{
    if (game.player.fuel_pct < 0.0)
    {
        bool exit_menu = false;
        do
        {
            process_events();
            exit_menu = handle_end_game_menu(global_menu_handler, game);

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
        draw_game(game);
        update_game(game);
        handle_end_game(global_menu_handler, game);


        // When the user types the escape key, handle the in-game paused menu
        handle_game_paused(global_menu_handler, game);

        // Exit the game when not in playing game mode
        if (global_menu_handler.game_state != PLAY_GAME_SCREEN) break;
        
    }

    // If user wants to return the home screen. Then return it
    if (global_menu_handler.game_state == HOME_SCREEN) return HOME_SCREEN;
    return END_GAME;
}


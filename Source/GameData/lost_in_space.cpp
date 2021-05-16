#include "splashkit.h"
#include <vector>
#include "enemies.h"
#include "lost_in_space.h"
#include "heads_up_display.h"
#include "player.h"
#include "../../Source/MenuData/menu_logic.h"
#include "power_up.h"
#include "lost_in_space_drawing.h"
#include "game_logic.h"

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

void check_collisions(game_data &game) 
{
    for (int index = game.power_ups.size() - 1; index >= 0; index--)
    {
        if (sprite_collision(game.player.player_sprite, game.power_ups[index].power_up_sprite))
        {
            play_sound_effect("pop");
            apply_power_up(game.player, game.power_ups[index].kind);
            remove_power_up(game.power_ups, index);
        }
    }

    // Prevent collisions with space fighter enemy
    for_all_space_fighters(game.enemies.space_fighters, [&] (space_fighter_data space_fighter)
    {
        check_entity_collision(game.player, space_fighter.space_fighter_sprite);
    });
}

void update_level_per_minute(game_data &game)
{
    // Change level every 10 seconds CURRENT
    double game_timer_in_seconds = get_ticks_as_milliseconds( timer_ticks(game.game_timer) ); // Convert milliseconds to seconds
    double game_level_per_10_secs = game.game_level * 60;  // Change to 60 to make per 60 seconds
    double draw_next_level_cooldown = get_ticks_as_milliseconds ( timer_ticks(game.level_up_timer_cooldown) );

    if (game_timer_in_seconds >= game_level_per_10_secs) 
    {
        game.game_level++;
        game.power_ups.clear(); 
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
    int power_up_occurence_limitation = get_power_up_occurence_limitation(game.game_level);

    // Check for the level of the game here
    update_level(game);


    // Add enemies for level 2, 


    // Have stuff pop up 



    
    // Perform movement and update the camera
    if (rnd(0, 1000) <= power_up_occurence_limitation)
        add_power_up(game.power_ups);

    check_collisions(game);

    update_player(game.player);
    update_power_ups(game.power_ups);

    update_all_enemies(game.enemies);
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

    add_space_fighter_to_game(game.enemies.space_fighters, 400, 400);
    
    while ( ! quit_requested() )
    {
        process_events();

        if (key_typed(M_KEY)) game.player.invincible = true;
        if (key_typed(N_KEY)) game.player.invincible = false;

        if ( key_typed (RIGHT_SHIFT_KEY) )
        {
            game.game_level++;
        }

        if ( key_typed (P_KEY) )
        {
            game.player.fuel_pct = 0.0;
        }

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


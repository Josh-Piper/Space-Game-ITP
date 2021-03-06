#include "splashkit.h"
#include <vector>
#include <algorithm>
#include "enemies.h"
#include "lost_in_space.h"
#include "heads_up_display.h"
#include "../../Source/MenuData/menu_logic.h"
#include "./Entities/player.h"
#include "./Entities/power_up.h"
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
    handle_collisions_player_and_powerup(
        game.power_ups, game.player);

    handle_collisions_player_and_space_fighters(
        game.enemies.space_fighters, game.player);

    handle_collisions_bullets_and_power_ups(
        game.enemies.space_fighters, game.power_ups);

    handle_collisions_player_and_bullets(
        game.enemies.space_fighters, game.player);
}

void update_level_per_minute(game_data &game)
{
    unsigned int ticks = timer_ticks(game.game_timer);
    double game_timer_in_seconds = get_ticks_as_seconds(ticks); 
    double game_level_per_60_secs = game.game_level * 60;
    double draw_next_level_cooldown = get_ticks_as_seconds ( 
        timer_ticks(game.level_up_timer_cooldown) );

    if (game_timer_in_seconds >= game_level_per_60_secs) 
    {
        game.game_level++;
        game.power_ups.clear(); 
        // Draw the next level information
        start_timer( game.level_up_timer_cooldown ); 
    }
    
    // if the draw next level has drawn for longer than 3 seconds then reset.
    if (draw_next_level_cooldown > 3.0) 
    {
        reset_timer(game.level_up_timer_cooldown);
        stop_timer(game.level_up_timer_cooldown);
    }
}

void update_level(game_data &game)
{
    update_level_per_minute(game);
}

void update_game(game_data &game)
{   
    update_level(game);
    generate_entities(game.power_ups, game.enemies, game.game_level);
    check_collisions(game);

    update_player(game.player);
    update_power_ups(game.power_ups);
    update_all_enemies(game.enemies, game.player);
}

void handle_game_paused(menu_handler_data &global_menu_handler, game_data &game)
{
    if (key_typed(ESCAPE_KEY))
    {
        bool exit_menu;
        do 
        {
            process_events();
            // Exit the game (go back to the menu screens) on click home
            exit_menu = handle_paused_screen_menu(global_menu_handler, game);
        } while ( ! exit_menu && ! quit_requested() );
    }
}

void handle_end_game(menu_handler_data &global_menu_handler, game_data &game)
{
    static const double PLAYER_DEATH_HEALTH = 0.0285;

    if (game.player.fuel_pct <= PLAYER_DEATH_HEALTH)
    {
        play_sound_effect("end_game_sound");
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

        handle_input(game.player);
        draw_game(game);
        update_game(game);
        handle_end_game(global_menu_handler, game);

        handle_game_paused(global_menu_handler, game); 
        if (global_menu_handler.game_state != PLAY_GAME_SCREEN) break; 
    }

    // If user wants to return the home screen. Then return it
    if (global_menu_handler.game_state == HOME_SCREEN) return HOME_SCREEN;
    return END_GAME;
}
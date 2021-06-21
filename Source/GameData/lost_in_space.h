#ifndef LOST_IN_SPACE
#define LOST_IN_SPACE

#include "splashkit.h"
#include "./Entities/player.h"
#include "./Entities/power_up.h"
#include "enemies.h"
#include <vector>

using std::vector;

/**
 * Game Data is used to manage the overall flow of the game and keep saved data
 * @field                                          player   
 * @field                                          power_ups   
 * @field                                          timer        
 * @field                                          game_level      
 * @field                                          enemies     
 */ 
struct game_data 
{
    player_data                 player;
    vector<power_up_data>       power_ups;      
    timer                       game_timer; 
    timer                       level_up_timer_cooldown;
    int                         game_level;
    enemy_handler_data          enemies;
};  

#include "../../Source/MenuData/menu_logic.h" //required for compiling properly

/**
 * Load all game resources via a bundle
 * 
 */ 
void load_resources();

/**
 * Returns a new_game() with a new player and 0 powerups
 * 
 */ 
game_data new_game();

/**
 * Check in-game collisions between any in-game powerup and the player
 * if true it will access apply_power_up and remove powerup
 * @param                                          game  
 */ 
void check_collisions(game_data &game);

/**
 * Update the current level of the game dependent on the game timer in ticks
 * @param                                          game
 */ 
void update_level(game_data &game);

/**
 * Handle updating the pre-existing drawn images
 * @param                                          game
 */ 
void update_game(game_data &game);

/**
 * Check if the game should be paused
 * Then handle the pause menu
 * @param                                          global_menu_game_handler  
 */ 
void handle_game_paused(menu_handler_data &global_menu_handler, 
    game_data &game);

/**
 * Handle the ending game scene
 * @param                                          global_menu_handler
 * @param                                          game
 */ 
void handle_end_game(menu_handler_data &global_menu_handler, game_data &game);

/**
 * Will return the game_state once the game is finished, thus, 
 * bring the user back to the original menu
 * or Quiting the game
 * Handles the Space Game loop
 */ 
game_state handle_game();

#endif
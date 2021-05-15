#ifndef LOST_IN_SPACE
#define LOST_IN_SPACE

#include "splashkit.h"
#include "player.h"
#include "power_up.h"
#include "enemies.h"
#include <vector>

using std::vector;

/**
 * Game Data is used to manage the overall flow of the game and keep saved data
 * 
 * @field   player          The user
 * @field   power_ups       Holds a vector of power_ups used to manage all power_ups within the game
 * @field   timer           The game timer is used to measure how long the game or action has transpired
 * @field   game_level      The level of the current game
 * @field   enemies         All enemies in the game
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
 * Create a new powerup with random coordinates and add it to the game's vector of power_ups
 * @param   game
 */ 
void add_power_up(game_data &game);

/**
 * Loop through all game powerups 
 * and update their position/animation
 * @param   power_ups
 */ 
void update_power_ups(const vector<power_up_data> power_ups);

/**
 * Apply the powerup to the ingame character,
 * this is done by editing the player's value
 * as per the power_ups kind
 * @param   game
 * @param   kind
 * 
 */ 
void apply_power_up(game_data &game, power_up_kind kind);

/**
 * Remove a specific power_up from the game
 * @param   game    Used to update the game's player
 * @param   kind    The type of power_up accessed
 */ 
void remove_power_up(game_data &game, int index);

/**
 * Check in-game collisions between any in-game powerup and the player
 * if true it will access apply_power_up and remove_power_up to give the in-game user effects
 * @param   game    Use the game's power_ups and player to check for collisions
 * 
 */ 
void check_collisions(game_data &game);

/**
 * Get the rate of occurrene powerups should spawn based on the game level
 * @param   game
 */ 
int get_power_up_occurence_limitation(const game_data &game);


/**
 * Update the current level of the game dependent on the game timer in ticks
 * @param   game
 */ 
void update_level(game_data &game);

/**
 * Handle updating the pre-existing drawn images
 * @param   game
 */ 
void update_game(game_data &game);


/**
 * Check if the game should be paused
 * Then handle the pause menu
 * @param global_menu_game_handler  
 */ 
void handle_game_paused(menu_handler_data &global_menu_handler, game_data &game);


/**
 * Handle the ending game scene
 * @param global_menu_handler
 * @param game
 */ 
void handle_end_game(menu_handler_data &global_menu_handler, game_data &game);


/**
 * Will return the game_state once the game is finished, thus, bring the user back to the original menu
 * or Quiting the game
 * Handles the Space Game loop
 */ 
game_state handle_game();



#endif
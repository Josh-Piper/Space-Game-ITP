#ifndef LOST_IN_SPACE
#define LOST_IN_SPACE

#include "splashkit.h"
#include "player.h"
#include "power_up.h"
#include <vector>

using std::vector;

/**
 * Load all game resources via a bundle
 * 
 */ 
void load_resources();

/**
 * Game Data is used to manage the overall flow of the game and keep saved data
 * 
 * @field   player          The user
 * @field   power_ups       Holds a vector of power_ups used to manage all power_ups within the game
 * @field   timer      Does somrthing
 */ 
struct game_data 
{
    player_data                 player;
    vector<power_up_data>       power_ups;      
    timer                       game_timer; 
};  

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
 * Draw all existing sprites in the game
 * @param   powerups
 */ 
void draw_power_ups(const vector<power_up_data> &powerups);

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
 * Handle updating the pre-existing drawn images
 * @param   game
 */ 
void update_game(game_data &game);

/**
 * Draw the game,
 * thus handle drawing the HUD, player and all powerups
 * @param   game
 */ 
void draw_game(const game_data &game);



#endif
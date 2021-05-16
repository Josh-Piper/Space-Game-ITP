
#ifndef GAME_LOGIC
#define GAME_LOGIC

#include <vector>
#include "splashkit.h"
#include "power_up.h"
#include "player.h"

/**
 * Data struct for handling information
 */ 
struct sprite_collision_data
{
    double left_x;
    double right_x;
    double top_y;
    double bottom_y;
};

/**
 * Create a new powerup with random coordinates and add it to the game's vector of power_ups
 * @param   power_ups
 */ 
void add_power_up(vector<power_up_data> &power_ups);

/**
 * Apply the powerup to the ingame character,
 * this is done by editing the player's value
 * as per the power_ups kind
 * @param   player
 * @param   kind
 * 
 */ 
void apply_power_up(player_data &player, power_up_kind kind);

/**
 * Loop through all game powerups 
 * and update their position/animation
 * @param   power_ups
 */ 
void update_power_ups(vector<power_up_data> &power_ups);

/**
 * Remove a specific power_up from the game
 * @param   power_ups    Used to update the game's player
 * @param   kind    The type of power_up accessed
 */ 
void remove_power_up(vector<power_up_data> &power_ups, int index);

/**
 * Create a new sprite collision data
 * This is a data class used to manage the coordinates of an entity
 * @param   sprite
 */ 
sprite_collision_data new_sprite_collision_data(sprite &sprite);

/**
 * Handle and check if the player has collided with an entity
 * @param   _player
 * @param   enemy_sprite
 */ 
void check_entity_collision(player_data &_player, sprite &enemy_sprite);

/**
 * Get the rate of occurrene powerups should spawn based on the game level
 * @param   game_level
 */ 
int get_power_up_occurence_limitation(int game_level);

#endif
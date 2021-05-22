
#ifndef GAME_LOGIC
#define GAME_LOGIC

#include <vector>
#include "splashkit.h"
#include "./Entities/power_up.h"
#include "./Entities/player.h"
#include "enemies.h"

/**
 * Data struct for handling collision information
 * @field                                          left_x
 * @field                                          right_x
 * @field                                          top_y
 * @field                                          bottom_y
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
 * @param                                          power_ups
 */ 
void add_power_up_to_game(vector<power_up_data> &power_ups);

/**
 * Apply the powerup to the ingame character,
 * this is done by editing the player's value
 * as per the power_ups kind
 * @param                                          player
 * @param                                          kind
 * 
 */ 
void apply_power_up(player_data &player, power_up_kind kind);

/**
 * Loop through all game powerups 
 * and update their position/animation
 * @param                                          power_ups
 */ 
void update_power_ups(vector<power_up_data> &power_ups);

/**
 * Remove a specific power_up from the game
 * @param                                          power_ups    Used to update the game's player
 * @param                                          kind    The type of power_up accessed
 */ 
void remove_power_up(vector<power_up_data> &power_ups, int index);

/**
 * Create a new sprite collision data
 * This is a data class used to manage the coordinates of an entity
 * @param                                          sprite
 */ 
sprite_collision_data new_sprite_collision_data(sprite &sprite);

/**
 * Handle and check if the player has collided with an entity
 * Return if a collision occurred
 * @param                                          _player
 * @param                                          enemy_sprite
 */ 
bool check_entity_collision(player_data &_player, sprite &enemy_sprite);

/**
 * Get the rate of occurrene powerups should spawn based on the game level
 * @param                                          game_level
 */ 
int get_power_up_occurence_limitation(int game_level);

/**
 * Return how many space fighters should spawn per level
 * @param                                          game_level
 */ 
int get_space_fighter_occurence_limitation(int game_level);

/**
 * Generate the game entities dependent on the current game level
 * @param                                          power_ups
 * @param                                          enemies
 * @param                                          game_level
 */ 
void generate_entities(vector<power_up_data> &power_ups, enemy_handler_data &enemies, int game_level);

/**
 * Handle the collision between a player and powerup
 * @param                                          power_ups
 * @param                                          player
 */ 
void handle_collisions_player_and_powerup(vector<power_up_data> &power_ups, player_data &player);

/**
 * Handle what happens during a collision with a player and space fighter
 * @param                                          space_fighters
 * @param                                          player
 */ 
void handle_collisions_player_and_space_fighters(vector<space_fighter_data> &space_fighters, player_data &player);

/**
 * Handle the collisions between the space fighter bullets and power ups
 * Deletes the powerup when it collides with a bullet
 * @param                                          space_fighters
 * @param                                          power_ups
 */ 
void handle_collisions_bullets_and_power_ups(vector<space_fighter_data> &space_fighters, vector<power_up_data> &power_ups);

/**
 * Delete a bullet if a player collides with it if the player is invincible or shielded
 * Otherwie the user gets dealth damage to their fuel.
 * @param                                          space_fighters
 * @param                                          player
 */ 
void handle_collisions_player_and_bullets(vector<space_fighter_data> &space_fighters, player_data &player);

#endif
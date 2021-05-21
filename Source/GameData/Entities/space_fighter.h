#ifndef SPACE_FIGHTER
#define SPACE_FIGHTER

#include "splashkit.h"
#include "player.h"
#include "power_up.h"
#include "bullet.h"
#include <vector>
#include <functional>

/**
 * A basic enemy - power level of 1
 * Shoots slow bullets towards the user
 * @field                                          space_fighter_sprite
 * @field                                          spawn_bullet_counter
 * @field                                          bullet_timer_id
 * @field                                          bullets
 */ 
struct space_fighter_data
{
    sprite                                         space_fighter_sprite;
    timer                                          spawn_bullet_counter;
    string                                         bullet_timer_id;
    vector<bullet>                                 bullets;                     
};

typedef std::function<void(space_fighter_data&)> space_fighter_function;
typedef std::function<void(space_fighter_data&, player_data&)> space_fighter_and_player_function;
typedef std::function<void(bullet&)> bullet_function;
typedef std::function<void(void)> all_enemies_function;

/**
 * Add a bullet to the space_fighter object
 * @param                                          space_fighter
 */ 
void add_bullet_to_space_fighter(space_fighter_data &space_fighter);


/**
 * Call a function to each space fighters bullets - used for updating these bullets
 * @param                                          space_fighters
 * @param                                          fn
 */ 
void for_all_space_fighters_bullets(vector<space_fighter_data> &space_fighters, bullet_function fn);

/**
 *  Call a function to each space fighters bullets when the bullets cannot be edited.
 * @param                                          space_fighters
 * @param                                          fn
 */ 
void for_all_space_fighters_bullets_drawing(const vector<space_fighter_data> &space_fighters, bullet_function fn);


/**
 * Generate a bullet for a space fighter every interval of x seconds
 * @param                                          space_fighters
 */ 
void generate_space_fighter_bullets(vector<space_fighter_data> &space_fighters);

/**
 * Control the lifecycle of a bullet, i.e. delete a bullet when it leaves a certain bound(s)
 * @param                                          space_fighters
 */ 
void handle_space_fighter_bullet_boundaries(vector<space_fighter_data> &space_fighters);

/**
 * Generate a random point within the game's space parameters
 */ 
point_2d generate_random_point_in_game();

/**
 * Create a space fighter located at x, y
 * @param                                          x
 * @param                                          y
 */ 
space_fighter_data create_enemy_space_fighter(double x, double y);

/**
 * Add a space fighter to a list of space fighters, this is done as stronger enemies 
 * contain a list of weaker one's
 * @param                                          space_fighters
 * @param                                          x
 * @param                                          y
 */ 
void add_space_fighter_to_game(vector<space_fighter_data> &space_fighters, double x, double y);

/**
 * Apply a function to every space fighter in a vector of them.
 * 
 * @param                                          space_fighters
 * @param                                          fn
 */ 
void for_all_space_fighters(vector<space_fighter_data> &space_fighters, space_fighter_function fn);

/**
 * Apply a function to every space fighter in a vector of them passing by CONSTANT.
 * 
 * @param                                          space_fighters
 * @param                                          fn
 */ 
void for_all_space_fighters_drawing(const vector<space_fighter_data> &space_fighters, space_fighter_function fn);

/**
 * Draw a space fighter
 * @param                                          entity
 */ 
void draw_enemy_space_fighter(const space_fighter_data &entity);

/**
 * Update a space fighter
 * @param                                          entity
 */ 
void update_enemy_space_fighter(const space_fighter_data &entity);

/**
 * Perform a space_player_and_fighter function that affects each space fighter and player
 * @param                                          space_fighters
 * @param                                          player
 * @param                                          space_fighter_and_player_fn
 */ 
void for_all_space_fighters_and_player(vector<space_fighter_data> &space_fighters, player_data &player, space_fighter_and_player_function space_fighter_and_player_fn);

/**
 * Update the space fighter to move towards a player
 * @param                                          fighter
 * @param                                          player
 */ 
void move_enemy_space_fighter_location_towards_player(space_fighter_data &fighter, player_data &player);

/**
 * Update all space fighters to move towards the user and update their location
 * @param                                          space_fighters
 * @param                                          player
 * 
 */ 
void update_all_space_fighters(vector<space_fighter_data> &space_fighters, player_data &player);

#endif
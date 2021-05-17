#ifndef ENEMIES
#define ENEMIES

#include "splashkit.h"
#include "player.h"
#include "power_up.h"
#include <vector>
#include <functional>

/**
 * A bullet that entities can shoot and use
 * @param                                          location
 * @param                                          image
 */ 
struct bullet
{
    point_2d                                       location;
    bitmap                                         image;
};

/**
 * A basic enemy - power level of 1
 * Shoots slow bullets towards the user
 * @param                                          space_fighter_sprite
 * @param                                          bullets
 */ 
struct space_fighter_data
{
    sprite                                         space_fighter_sprite;
    vector<bullet>                                 bullets;                     
};

/**
 * (NOT IMPLEMENTED)
 * A basic enemy leader - power level of 2 
 * Leads a squadron of space fighters
 * @param                                          space_leader_sprite
 * @param                                          reinforcements
 */ 
struct space_leader_data
{
    sprite                                         space_leader_sprite;
    vector<space_fighter_data>                     reinforcements;
};

/**
 * (NOT IMPLEMENTED)
 *  A planet that inhibits lifeforms.
 * Contains a reinforcements of space leaders which have their own platoons
 * @param                                          planet_warfare_sprite
 * @param                                          reinforcements
 */ 
struct planet_warefare_data
{
    sprite                                         planet_warefare_sprite;
    vector<space_leader_data>                      reinforcements;
};

/**
 * (NOT IMPLEMENTED)
 * A dying sun that gives life to multiple planets
 * The strongest enemy in Lost in Space
 * Contains a list of planets that rely on it
 * @param                                          dying_sun_sprite
 * @param                                          reinforcements
 */ 
struct dying_sun_data
{
    sprite                                         dying_sun_sprite;
    vector<planet_warefare_data>                   reinforcements;
};

/**
 * Enemy Handler Data
 * A data class handling all the types of enemies in the game
 * @param                                          space_fighters
 * @param                                          space_leaders
 * @param                                          planet_warefare_entities
 * @param                                          dying_sun_entities
 */ 
struct enemy_handler_data
{
    vector<space_fighter_data>                     space_fighters;
    vector<space_leader_data>                      space_leaders;
    vector<planet_warefare_data>                   planet_warefare_entities;
    vector<dying_sun_data>                         dying_sun_entities;
};

/**
 * Generate a random point within the game's space parameters
 */ 
point_2d generate_random_point_in_game();

typedef std::function<void(space_fighter_data)> space_fighter_function;

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
void for_all_space_fighters(vector<space_fighter_data> space_fighters, space_fighter_function fn);

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
 * Draw all the enemies in the game
 * @param                                          entities
 */ 
void draw_all_enemies(const enemy_handler_data &enemies);

/**
 * Update all space fighters to move towards the user and update their location
 * @param                                          space_fighters
 * @param                                          player
 * 
 */ 
void update_all_space_fighters(vector<space_fighter_data> &space_fighters, player_data &player);

/**
 * Update all enemies in the game, have them move towards the user 
 * 
 * @param                                          enemies
 * @param                                          player
 */ 
void update_all_enemies(enemy_handler_data &enemies, player_data &player);




#endif
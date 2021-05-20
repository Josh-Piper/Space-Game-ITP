#ifndef ENEMIES
#define ENEMIES

#include "splashkit.h"
#include "player.h"
#include "power_up.h"
#include <vector>
#include <functional>

/**
 * A bullet that entities can shoot and use
 * @param                                          original_location
 * @param                                          bullet_sprite
 */ 
struct bullet
{
    point_2d                                       original_location;
    sprite                                         bullet_sprite;
};

/**
 * A basic enemy - power level of 1
 * Shoots slow bullets towards the user
 * @param                                          space_fighter_sprite
 * @param                                          spawn_bullet_counter
 * @param                                          bullet_timer_id
 * @param                                          bullets
 */ 
struct space_fighter_data
{
    sprite                                         space_fighter_sprite;
    timer                                          spawn_bullet_counter;
    string                                         bullet_timer_id;
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

typedef std::function<void(space_fighter_data&)> space_fighter_function;
typedef std::function<void(space_fighter_data&, player_data&)> space_fighter_and_player_function;
typedef std::function<void(void)> all_enemies_function;

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
 * Update the space fighter to move towards a player
 * @param                                          fighter
 * @param                                          player
 */ 
void move_enemy_space_fighter_location_towards_player(space_fighter_data &fighter, player_data &player);

/**
 * Perform a space_player_and_fighter function that affects each space fighter and player
 * @param                                          space_fighters
 * @param                                          player
 * @param                                          space_fighter_and_player_fn
 */ 
void for_all_space_fighters_and_player(vector<space_fighter_data> &space_fighters, player_data &player, space_fighter_and_player_function space_fighter_and_player_fn);


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
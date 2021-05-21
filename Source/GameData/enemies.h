#ifndef ENEMIES
#define ENEMIES

#include "splashkit.h"
#include "./Entities/player.h"
#include "./Entities/power_up.h"
#include "./Entities/bullet.h"
#include "./Entities/space_fighter.h"
#include <vector>
#include <functional>

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
 * Draw all the enemies in the game
 * @param                                          entities
 */ 
void draw_all_enemies(const enemy_handler_data &enemies);

/**
 * Update all enemies in the game, have them move towards the user 
 * 
 * @param                                          enemies
 * @param                                          player
 */ 
void update_all_enemies(enemy_handler_data &enemies, player_data &player);

#endif
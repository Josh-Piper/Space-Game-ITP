#ifndef LOST_IN_SPACE_DRAWING
#define LOST_IN_SPACE_DRAWING

#include "splashkit.h"
#include "lost_in_space.h"
#include "./Entities/power_up.h"

/**
 * Draw the level up screen
 * @param                                          game
 */ 
void draw_next_level_information(const game_data &game);

/**
 * Draw all existing sprites in the game
 * @param                                          powerups
 */ 
void draw_power_ups(const vector<power_up_data> &powerups);

/**
 * Draw the game,
 * thus handle drawing the HUD, player and all powerups
 * @param                                          game
 */ 
void draw_game(const game_data &game);

#endif
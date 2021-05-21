#ifndef HEADS_UP_DISPLAY
#define HEADS_UP_DISPLAY

#include "splashkit.h"
#include "heads_up_display.h"
#include "lost_in_space.h"
#include "enemies.h"
#include "./Entities/player.h"
#include "./Entities/power_up.h"
#include "./Entities/space_fighter.h"

enum time_data
{
    SECONDS,
    MINUTES,
    HOURS

};

/**
 * Remove the cords prefix filler text, i.e. @pt ...
 * @param                                          cords
 */ 
string remove_cords_prefix_filler_text(string cords);

/**
 * Convert the cords string to one decimal place
 * Remove the filler symbols.
 * @param cords     the x and y cords to be converted
 */ 
string get_heads_up_display_cords_as_string(point_2d cords);

/**
 * Convert a number to two decimal point
 * @param                                          number
 */ 
string convert_number_to_two_dp(string number);


/**
 * Add a suffix to a time, i.e. seconds, minutes etc.
 * @param                                          current_time      The current text
 * @param                                          suffix          The suffix to add to the end of result
 */     
string append_time_suffix(string current_time, time_data suffix);

/**
 * Convert ticks to seconds
 * @param                                          ticks
 */ 
double get_ticks_as_seconds(unsigned int ticks);

/**
 * Convert millisecond to seconds
 * @param                                          ticks
 */
string convert_milliseconds_to_seconds(unsigned int ticks);


/**
 * Get the mini map coordinates of a power_up
 * @param                                          power_up
 */ 
point_2d mini_map_coordinate(const power_up_data &power_up);

/**
 * Get the mini map coordinates of a space fighter
 * @param                                          space_fighter
 */ 
point_2d mini_map_coordinate(const space_fighter_data &space_fighter);

/**
 * Get the mini map coordinates of a player
 * @param                                          x 
 * @param                                          y
 */ 
point_2d mini_map_coordinate_player(double x, double y);

/**
 * Draw the mini map location for all power ups
 * @param                                          power_ups
 */ 
void draw_mini_map_location_for_powerups(const vector<power_up_data> &power_ups);

/**
 * Draw the mini map location for the player
 * @param                                          player
 */ 
void draw_mini_map_location_for_player(const player_data &player);

/**
 * Draw the minimap location for all space fighters
 * @param                                          space_fighters
 */ 
void draw_mini_map_location_for_space_fighters(const vector<space_fighter_data> space_fighters);

/**
 * Draw the minimap and each entity as a pixel on the map
 * @param                                          power_ups
 * @param                                          player
 * @param                                          enemies
 */ 
void draw_mini_map(const vector<power_up_data> &power_ups, const player_data &player, const enemy_handler_data &enemies);

/**
 * Draw the HUD background
 * @param                                          game  
 */ 
void draw_heads_up_display_background(const game_data &game);

/**
 * Handle the drawing of the HUD
 * @param                                          game    
 */ 
void draw_heads_up_display(const game_data &game);


#endif
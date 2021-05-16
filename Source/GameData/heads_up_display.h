#ifndef HEADS_UP_DISPLAY
#define HEADS_UP_DISPLAY

#include "splashkit.h"
#include "heads_up_display.h"
#include "lost_in_space.h"
#include "player.h"
#include "power_up.h"


enum time_data
{
    SECONDS,
    MINUTES,
    HOURS

};

/**
 * Convert the cords string to one decimal place
 * Remove the filler symbols.
 * @param cords     the x and y cords to be converted
 */ 
string get_heads_up_display_cords_as_string(point_2d cords);

/**
 * Add a suffix to a time, i.e. seconds, minutes etc.
 * @param   result      The current text
 * @param   suffix      The suffix to add to the end of result
 */ 
string append_time_suffix(string result, time_data suffix);

/**
 * Convert ticks to milliseconds
 * @param ticks
 */ 
double get_ticks_as_milliseconds(unsigned int ticks);

/**
 * Convert millisecond to seconds
 * @param   ticks
 */
string convert_milliseconds_to_seconds(unsigned int ticks);


/**
 * Get the mini map coordinates of a power_up
 * @param power_up
 */ 
point_2d mini_map_coordinate(const power_up_data &power_up);

/**
 * Get the mini map coordinates of a player
 * @param x 
 * @param y
 */ 
point_2d mini_map_coordinate_player(double x, double y);

/**
 * Draw the minimap
 * @param power_ups
 * 
 */ 
void draw_mini_map(const vector<power_up_data> &power_ups, const player_data &player);

/**
 * Draw the HUD
 * @param game  
 */ 
void draw_heads_up_display_background(const game_data &game);


/**
 * Handle the drawing of the HUD
 * @param player    The player object, requires its details for the HUD screen
 */ 
void draw_heads_up_display(const game_data &game);


#endif
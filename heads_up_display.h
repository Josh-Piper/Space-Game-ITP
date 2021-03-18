#include "splashkit.h"
#include "player.h"

/**
 * Convert the cords string to one decimal place
 * Remove the filler symbols.
 * @param cords     the x and y cords to be converted
 */ 
string get_heads_up_display_cords_as_string(point_2d cords);

/**
 * Draw the background of the HUD
 */ 
void draw_heads_up_display_background();

/**
 * Handle the drawing of the HUD
 * @param player    The player object, requires its details for the HUD screen
 */ 
void draw_heads_up_display(const player_data &player); 
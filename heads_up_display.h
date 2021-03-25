#ifndef HEADS_UP_DISPLAY
#define HEADS_UP_DISPLAY

#include "splashkit.h"
#include "heads_up_display.h"
#include "lost_in_space.h"
#include "player.h"
#include "power_up.h"

/**
 * Convert the cords string to one decimal place
 * Remove the filler symbols.
 * @param cords     the x and y cords to be converted
 */ 
string get_heads_up_display_cords_as_string(point_2d cords);

void draw_hud(const vector<power_up_data> &power_ups);

void draw_heads_up_display_background(const game_data &game);


/**
 * Handle the drawing of the HUD
 * @param player    The player object, requires its details for the HUD screen
 */ 
void draw_heads_up_display(const game_data &game);


#endif
#ifndef POWER_UPS_FOR_PLAYER
#define POWER_UPS_FOR_PLAYER

#include "splashkit.h"

/**
 * Different options for the kind of power up.
 * Adjusts the image used.
 */
enum power_up_kind 
{
    FUEL,
    SHIELD,
    POTION,
    DROPS,
    DIAMOND,
    COIN
};

/**
 * Power up data object
 * @field                                          kind               
 * @field                                          power_up_sprite    
 */
struct power_up_data {
    power_up_kind kind;
    sprite power_up_sprite;
};

/**
 * Return the bitmap for drawing purposes.
 * Uses the power_up_kind for conversion
 * @param                                          option 
 */ 
bitmap power_up_bitmap(power_up_kind option);


/**
 * Creates a new power up in a desired location
 * @param                                          x   
 * @param                                          y     
 */ 
power_up_data new_power_up(double x, double y);


/**
 * Draws the powerup
 * @param                                          power_up  
 */ 
void draw_power_up(const power_up_data &power_up);


/**
 * Updates the movement of the power up
 * @param                                          power_up  
 */ 
void update_power_up(power_up_data &power_up);

#endif
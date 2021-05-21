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
 * The power up data keeps track of all of the information related to the powerup.
 * @field                                          kind                    The kind of power up
 * @field                                          power_up_sprite         The power ups sprite - used to track position and movement
 */
struct power_up_data {
    power_up_kind kind;
    sprite power_up_sprite;
};

/**
 * Return the bitmap for drawing purposes.
 * Uses the power_up_kind for conversion
 * @param                                          option    The power up kind to be converted
 */ 
bitmap power_up_bitmap(power_up_kind option);


/**
 * Creates a new power up in a desired location
 * @param                                          x     the desired x location
 * @param                                          y     the desired y location
 */ 
power_up_data new_power_up(double x, double y);


/**
 * Draws the powerup
 * @param                                          power_up  The powerup to be drawn
 */ 
void draw_power_up(const power_up_data &power_up);


/**
 * Updates the movement of the power up
 * @param                                          power_up  The powerup to be updated
 */ 
void update_power_up(power_up_data &power_up);


#endif
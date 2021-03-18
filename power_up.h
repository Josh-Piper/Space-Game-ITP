#ifndef POWER_UPS_FOR_PLAYER
#define POWER_UPS_FOR_PLAYER


#include "./include/splashkit/splashkit.h"


enum power_up_kind 
{
    FUEL,
    SHIELD,
    POTION,
    DROPS,
    DIAMOND,
    COIN
};

struct power_up_data {
    power_up_kind kind;
    sprite power_up_sprite;


};

bitmap get_bitmap_for_power(power_up_kind option);


power_up_data new_power_up(double x, double y);



void draw_power_up(const power_up_data &power_up);



void update_power_up(power_up_data &power_up);


#endif
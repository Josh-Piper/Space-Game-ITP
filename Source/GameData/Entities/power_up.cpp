#include "splashkit.h"
#include "power_up.h"

bitmap power_up_bitmap(power_up_kind option) {
    bitmap result;
    switch (option) 
    {
        case FUEL: result = bitmap_named("fuel"); break;
        case SHIELD: result = bitmap_named("shield"); break;
        case POTION: result = bitmap_named("potion"); break;
        case DROPS: result = bitmap_named("drops"); break;
        case DIAMOND: result = bitmap_named("diamond"); break;
        default: result = bitmap_named("coin"); break;
    }
    return result;
}

power_up_data new_power_up(double x, double y) 
{
    power_up_data result;
    result.kind =  static_cast<power_up_kind>(rnd(6));
    result.power_up_sprite = create_sprite ( power_up_bitmap(result.kind) );
    sprite_set_position(result.power_up_sprite, point_at(x, y));
    sprite_set_dx(result.power_up_sprite, rnd() * 0.3 - 0.5); 
    sprite_set_dy(result.power_up_sprite, rnd() * 0.3 - 0.5); 
    return result;
}

void draw_power_up(const power_up_data &power_up)
{
    draw_sprite(power_up.power_up_sprite);
}

void update_power_up(power_up_data &power_up)
{
    update_sprite(power_up.power_up_sprite);
}
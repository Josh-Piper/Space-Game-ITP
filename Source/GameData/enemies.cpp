#include "splashkit.h"
#include "enemies.h"
#include "player.h"
#include "lost_in_space.h"
#include <functional>

typedef std::function<void(space_fighter_data)> space_fighter_function;
typedef std::function<void(void)> all_enemies_function;

space_fighter_data create_enemy_space_fighter(double x, double y)
{
    space_fighter_data result;
    result.space_fighter_sprite = create_sprite ( bitmap_named("pegasi") ); //ship_bitmap(PEGASI)
    
    sprite_set_position(result.space_fighter_sprite, point_at(x, y));

    return result;
}

void add_space_fighter_to_game(vector<space_fighter_data> &space_fighters, double x, double y)
{
    space_fighter_data space_fighter = create_enemy_space_fighter(x, y);
    space_fighters.push_back(space_fighter);
}

void for_all_space_fighters(vector<space_fighter_data> space_fighters, space_fighter_function fn)
{
   // write_line("for all space fighters");
    for (space_fighter_data space_fighter: space_fighters)
    {
        //write_line("Atleast 1 enemy");
        fn(space_fighter);
    }
}

void draw_enemy_space_fighter(const space_fighter_data &entity)
{
    draw_sprite(entity.space_fighter_sprite);
}

void update_enemy_space_fighter(const space_fighter_data &entity)
{
    update_sprite(entity.space_fighter_sprite);
}

void draw_all_enemies(const enemy_handler_data &enemies)
{
    for_all_space_fighters(enemies.space_fighters, draw_enemy_space_fighter);
}

void update_all_enemies(const enemy_handler_data &enemies)
{
    for_all_space_fighters(enemies.space_fighters, update_enemy_space_fighter);
}













// space_leader_data create_enemy_space_leaader(double x, double y)
// {
//     space_leader_data result;
//     result.space_leader_sprite = create_sprite ( ship_bitmap(GLIESE) );

//     sprite_set_position(result.space_leader_sprite, point_at(x, y));

//     return result;
// }

// planet_warefare_data create_enemy_planet(double x, double y)
// {
//     planet_warefare_data result;
//     sprite_set_position(result.planet_warefare_sprite, point_at(x, y));

//     return result;
// }

// dying_sun_data create_enemy_dying_sun(double x, double y)
// {
//     dying_sun_data result;
//     sprite_set_position(result.dying_sun_sprite, point_at(x, y));

//     return result;
// }













// power_up_data new_power_up(double x, double y) 
// {
//     power_up_data result;
//     result.kind =  static_cast<power_up_kind>(rnd(6));
//     result.power_up_sprite = create_sprite ( power_up_bitmap(result.kind) );
//     sprite_set_position(result.power_up_sprite, point_at(x, y));
//     sprite_set_dx(result.power_up_sprite, rnd() * 0.3 - 0.5); 
//     sprite_set_dy(result.power_up_sprite, rnd() * 0.3 - 0.5); 
//     return result;
// }

// void draw_power_up(const power_up_data &power_up)
// {
//     draw_sprite(power_up.power_up_sprite);
// }

// void update_power_up(power_up_data &power_up)
// {
//     update_sprite(power_up.power_up_sprite);
// }


    // // Allow the player to switch ships
    // if (key_typed(NUM_1_KEY))
    //     player_switch_to_ship(player, AQUARII);
    // if (key_typed(NUM_2_KEY))
    //     player_switch_to_ship(player, GLIESE);
    // if (key_typed(NUM_3_KEY))
    //     player_switch_to_ship(player, PEGASI);

    // sprite_add_layer(result.player_sprite, ship_bitmap(GLIESE), "GLIESE");
    // sprite_add_layer(result.player_sprite, ship_bitmap(PEGASI), "PEGASI");

    // // Default to layer 0 = Aquarii so hide others
    // sprite_hide_layer(result.player_sprite, 1);
    // sprite_hide_layer(result.player_sprite, 2);

//     bitmap ship_bitmap(ship_kind kind)
// {
//     switch (kind)
//     {
//     case AQUARII:
//         return bitmap_named("aquarii");
//     case GLIESE:
//         return bitmap_named("gliese");
//     default:
//         return bitmap_named("pegasi");
//     }
// }

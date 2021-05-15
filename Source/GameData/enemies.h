#ifndef ENEMIES
#define ENEMIES

#include "splashkit.h"
#include <vector>
#include <functional>

struct space_fighter_data
{
    sprite                                         space_fighter_sprite;
};

struct space_leader_data
{
    sprite                                         space_leader_sprite;
    vector<space_fighter_data>                     reinforcements;
};

struct planet_warefare_data
{
    sprite                                         planet_warefare_sprite;
    vector<space_leader_data>                      reinforcements;
};

struct dying_sun_data
{
    sprite                                         dying_sun_sprite;
    vector<planet_warefare_data>                   reinforcements;
};

struct enemy_handler_data
{
    vector<space_fighter_data>                     space_fighters;
    vector<space_leader_data>                      space_leaders;
    vector<planet_warefare_data>                   planet_warefare_entities;
    vector<dying_sun_data>                         dying_sun_entities;
};

typedef std::function<void(space_fighter_data)> space_fighter_function;

space_fighter_data create_enemy_space_fighter(double x, double y);

void add_space_fighter_to_game(vector<space_fighter_data> &space_fighters, double x, double y);

void for_all_space_fighters(vector<space_fighter_data> space_fighters, space_fighter_function fn);

void draw_enemy_space_fighter(const space_fighter_data &entity);

void update_enemy_space_fighter(const space_fighter_data &entity);

void draw_all_enemies(const enemy_handler_data &enemies);

void update_all_enemies(const enemy_handler_data &enemies);



#endif
#ifndef LOST_IN_SPACE
#define LOST_IN_SPACE

#include "splashkit.h"
#include "player.h"
#include "power_up.h"
#include "heads_up_display.h"
#include <vector>

using std::vector;



struct game_data 
{
    player_data                 player;
    vector<power_up_data>       power_ups;      
    //game_timer                  timer; 
};  

void load_resources();

game_data new_game();

void add_power_up(game_data &game);

void update_power_ups(vector<power_up_data> power_ups);

void draw_power_ups(const vector<power_up_data> &powerups);

void apply_power_up(game_data &game, power_up_kind kind);

void remove_power_up(game_data &game, int index);

void check_collisions(game_data &game);

void update_game(game_data &game);

void draw_game(const game_data &game);



#endif
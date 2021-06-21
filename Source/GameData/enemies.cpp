#include "splashkit.h"
#include "enemies.h"
#include "./Entities/player.h"
#include "./Entities/space_fighter.h"
#include <functional>

void draw_all_enemies(const enemy_handler_data &enemies)
{
    for_all_space_fighters_drawing(enemies.space_fighters,
        draw_enemy_space_fighter);

    for_all_space_fighters_bullets_drawing(enemies.space_fighters, 
        draw_bullet);
}

void update_all_enemies(enemy_handler_data &enemies, player_data &player)
{
    update_all_space_fighters(enemies.space_fighters, player);
}
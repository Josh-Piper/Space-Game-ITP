#include "splashkit.h"
#include "./Entities/player.h"
#include "./Entities/power_up.h"
#include "game_logic.h"
#include "enemies.h"
#include <vector>
#include <map>

const int MINIMUM_SPACE_LOCATION = -1500;
const int MAXIMUM_SPACE_LOCATION = 1500;

point_2d generate_random_point_in_game()
{
    point_2d result;
    result.x = rnd(MINIMUM_SPACE_LOCATION, MAXIMUM_SPACE_LOCATION);
    result.y = rnd(MINIMUM_SPACE_LOCATION, MAXIMUM_SPACE_LOCATION);   
    return result; 
}

void add_power_up_to_game(vector<power_up_data> &power_ups)
{
    point_2d random_point = generate_random_point_in_game();
    power_up_data result = new_power_up(random_point.x, random_point.y);
    power_ups.push_back( result );
}

void apply_power_up(player_data &player, power_up_kind kind)
{
    if (kind == FUEL)
        apply_fuel_power_up_to_player(player);
    
    else if (kind == SHIELD)    
        apply_shield_power_up_to_player(player);

    else if (kind == POTION && player.power_up_counter == 0.0 &&
            !(player.invincible))
        apply_potion_power_up_to_player(player);
    
    else if (kind == DROPS)
        apply_drops_power_up_to_player(player);
    
    else if (kind == DIAMOND)
        apply_diamond_power_up_to_player(player);
     
    else if (kind == COIN) 
        apply_coin_power_up_to_player(player);

    increment_player_power_up_count(player);
    set_player_current_power_up_image(player, power_up_bitmap(kind));
}

void update_power_ups(vector<power_up_data> &power_ups) 
{
    for (power_up_data &power_up: power_ups)
        update_power_up(power_up);
}

void remove_power_up(vector<power_up_data> &power_ups, int index)
{
    power_ups[index] = power_ups[power_ups.size() - 1];
    power_ups.pop_back();
}

sprite_collision_data new_sprite_collision_data(sprite &sprite)
{
    sprite_collision_data result;

    double half_width = sprite_width(sprite) / 2;
    double half_height = sprite_height(sprite) / 2;
    result.left_x = sprite_x(sprite) - half_width; 
    result.top_y = sprite_y(sprite) - half_height;
    result.right_x = result.left_x + half_width * 2;
    result.bottom_y = result.top_y + half_height * 2;

    return result;
}

void update_player_collision(bool is_left_collision, bool is_right_collision,
    player_data &player, double left, double right)
{
        if (is_left_collision) 
            sprite_set_x(player.player_sprite, (left - 0.05));
        if (is_right_collision) 
            sprite_set_x(player.player_sprite, (right + 0.05));
        if (!player.invincible && ! ( player.power_up_counter > 0) ) 
            player.fuel_pct -= 0.01;
}

bool check_entity_collision(player_data &_player, sprite &enemy_sprite)
{
    sprite player_sprite = _player.player_sprite;
    sprite_collision_data player = new_sprite_collision_data(player_sprite);
    sprite_collision_data fighter = new_sprite_collision_data(enemy_sprite);

    if ( sprite_collision ( player_sprite, enemy_sprite ) )
    {
        bool check_left_collision = player.right_x > fighter.left_x && 
            !(player.right_x > fighter.right_x);
        bool check_right_collision = player.left_x < fighter.right_x && 
            !(player.left_x <  fighter.left_x);

        update_player_collision(check_left_collision, check_right_collision,
            _player, player.left_x, player.right_x);

        return true;
    } 
    return false;
}

int get_power_up_occurence_limitation(int game_level)
{
    int result;
    switch (game_level)
    {
        case 1: result = 30; break;
        case 2: result = 28; break;
        case 3: result = 26; break;
        case 4: result = 24; break;
        case 5: result = 22; break;
        case 6: result = 18; break;
        case 7: result = 15; break;
        case 8: result = 13; break;
        case 9: result = 10; break;
        default: result = 5; break;
    }
    return result;
}

int get_space_fighter_occurence_limitation(int game_level)
{
    static const map<int, int> SPACE_FIGHTERS_OCCURRENCES
    {
        { 1, -1 },
        { 2, 1 },
        { 3, 2 },
        { 4, 3 },
        { 5, 4 },
        { 6, 5 },
        { 7, 6 },
        { 8, 7 },
        { 9, 10 },
        { 10, 15 },
    };

    auto result = SPACE_FIGHTERS_OCCURRENCES.find(game_level);
    if (result != SPACE_FIGHTERS_OCCURRENCES.end())
    {
        return result->second;
    }

    return 50;
}

void generate_entities(vector<power_up_data> &power_ups, 
    enemy_handler_data &enemies, int game_level)
{
    static const int RANDOM_MIN = 0, RANDOM_MAX = 1000; 

    int power_up_occurence_limitation = 
        get_power_up_occurence_limitation(game_level);

    int space_fighter_occurence_limitation = 
        get_space_fighter_occurence_limitation(game_level);

    // Create powerups
    if (rnd(RANDOM_MIN, RANDOM_MAX) <= power_up_occurence_limitation)
        add_power_up_to_game(power_ups);

    // Create space fighter enemy once past level 2
    if (rnd(RANDOM_MIN, RANDOM_MAX) <= space_fighter_occurence_limitation)
    {
        point_2d random = generate_random_point_in_game();

        add_space_fighter_to_game(enemies.space_fighters, random.x, random.y);
    }
}

void handle_collisions_player_and_powerup(vector<power_up_data> &power_ups, 
    player_data &player)
{
    for (int index = power_ups.size() - 1; index >= 0; index--)
    {
        power_up_data current = power_ups[index];

        if (sprite_collision(player.player_sprite, current.power_up_sprite))
        {
            apply_power_up(player, current.kind);
            remove_power_up(power_ups, index);
        }
    }
}

void handle_collisions_player_and_space_fighters(
        vector<space_fighter_data> &space_fighters, player_data &player)
{
    // Kill the entity if invincible or shielded.

    int index_of_current_fighter = 0;
    for_all_space_fighters(space_fighters, [&](space_fighter_data space_fighter)
    {  
        if ( check_entity_collision(player, space_fighter.space_fighter_sprite)) 
        {
           if (player.invincible || player.power_up_counter > 0)
           {
                remove_space_fighter(space_fighters, index_of_current_fighter);
                play_sound_effect("splat");
           }    
        }
        index_of_current_fighter++;
    });
}

void handle_collisions_bullets_and_power_ups(
    vector<space_fighter_data> &space_fighters, vector<power_up_data> &power_ups)
{
    // delete_power_up_on_bullet_impact
    for_all_space_fighters_bullets(space_fighters, [&] (bullet &bullet)
    {
        for (int index = 0; index < power_ups.size(); index++)
        {
            power_up_data current = power_ups[index];
            if (sprite_collision(bullet.bullet_sprite, current.power_up_sprite))
                remove_power_up(power_ups, index);
        }
    });
}

void handle_collisions_player_and_bullets(
    vector<space_fighter_data> &space_fighters, player_data &player)
{
    // delete_power_up_on_bullet_impact
    for_all_space_fighters(space_fighters, [&] (space_fighter_data &space_fighter) 
    {
        for (int index = 0; index < space_fighter.bullets.size(); index++)
        {
            bullet current = space_fighter.bullets[index];
            if ( check_entity_collision (player, current.bullet_sprite) )
            {
                if ( !(player.invincible) && !(player.power_up_counter > 0) ) 
                    player.fuel_pct -= 0.25;

                delete_bullet(space_fighter.bullets, index);  
                play_sound_effect("splat");
            }
        }
    });
}
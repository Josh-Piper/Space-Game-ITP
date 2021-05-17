#include "splashkit.h"
#include <vector>
#include <map>
#include "game_logic.h"
#include "player.h"
#include "power_up.h"
#include "enemies.h"

const int MINIMUM_SPACE_LOCATION = -1500;
const int MAXIMUM_SPACE_LOCATION = 1500;

point_2d generate_random_point_in_game()
{
    point_2d result;
    result.x = rnd(MINIMUM_SPACE_LOCATION, MAXIMUM_SPACE_LOCATION);
    result.y = rnd(MINIMUM_SPACE_LOCATION, MAXIMUM_SPACE_LOCATION);   
    return result; 
}

void add_power_up(vector<power_up_data> &power_ups)
{
    point_2d random_point = generate_random_point_in_game();
    power_up_data result = new_power_up(random_point.x, random_point.y);
    power_ups.push_back( result );
}

void apply_power_up(player_data &player, power_up_kind kind)
{
    if (kind == FUEL)
    {
        player.fuel_pct +=  0.20;
        if (player.fuel_pct >= 1.0) player.fuel_pct = 1.0;
    } 
    else if (kind == SHIELD)
    {
        player.power_up_counter = 1.0;
    }
    else if (kind == POTION && player.power_up_counter == 0.0)
    {
        player.fuel_pct -= 0.15;
    }
    else if (kind == DROPS)
    {
        player.score += 5;
    }
    else if (kind == DIAMOND)
    {
        player.score += 50;
    } 
    else if (kind == COIN) 
    {   
        player.score += 1;
    }

    player.total_power_ups += 1;
    player.current_power_up = power_up_bitmap(kind);
}

void update_power_ups(vector<power_up_data> &power_ups) 
{
    for (int i; i < power_ups.size(); i++)
        update_power_up(power_ups[i]);
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

bool check_entity_collision(player_data &_player, sprite &enemy_sprite)
{
    sprite player_sprite = _player.player_sprite;
    sprite_collision_data player = new_sprite_collision_data(player_sprite);
    sprite_collision_data fighter = new_sprite_collision_data(enemy_sprite);

    if ( sprite_collision ( player_sprite, enemy_sprite ) )
    {
        bool check_left_collision = player.right_x > fighter.left_x && !(player.right_x > fighter.right_x);
        bool check_right_collision = player.left_x < fighter.right_x && !(player.left_x <  fighter.left_x);

        if (check_left_collision) sprite_set_x(player_sprite, (player.left_x - 0.05));
        if (check_right_collision) sprite_set_x(player_sprite, (player.right_x + 0.05));
        if (!_player.invincible && ! ( _player.power_up_counter > 0) ) _player.fuel_pct -= 0.01;

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
        { 1, 0 },
        { 2, 1 },
        { 3, 3 },
        { 4, 5 },
        { 5, 15 },
        { 6, 20 },
        { 7, 25 },
        { 8, 30 },
        { 9, 40 },
        { 10, 45 },
    };

    return SPACE_FIGHTERS_OCCURRENCES.at(game_level);
}

void generate_entities(vector<power_up_data> &power_ups, enemy_handler_data &enemies ,int game_level)
{
    // Create powerups
    static const int RANDOM_MIN = 0, RANDOM_MAX = 1000; 
    int power_up_occurence_limitation = get_power_up_occurence_limitation(game_level), space_fighter_occurence_limitation = get_space_fighter_occurence_limitation(game_level);

    if (rnd(RANDOM_MIN, RANDOM_MAX) <= power_up_occurence_limitation)
        add_power_up(power_ups);

    // Create space fighter enemy once past level 2
    if (rnd(RANDOM_MIN, RANDOM_MAX) <= space_fighter_occurence_limitation)
    {
        point_2d fighter_location = generate_random_point_in_game();
        add_space_fighter_to_game(enemies.space_fighters, fighter_location.x, fighter_location.y);
    }
}

void handle_collisions_player_and_powerup(vector<power_up_data> &power_ups, player_data &player)
{
    for (int index = power_ups.size() - 1; index >= 0; index--)
    {
        if (sprite_collision(player.player_sprite, power_ups[index].power_up_sprite))
        {
            play_sound_effect("pop");
            apply_power_up(player, power_ups[index].kind);
            remove_power_up(power_ups, index);
        }
    }
}

void handle_collisions_player_and_space_fighters(vector<space_fighter_data> &space_fighters, player_data &player)
{
    // Prevent collisions with space fighter enemy and kill the entity if invincible or shielded -> change to iterator loop for safe deletions
    int index_of_current_fighter = 0;
    for_all_space_fighters(space_fighters, [&] (space_fighter_data space_fighter)
    {  
        if ( check_entity_collision(player, space_fighter.space_fighter_sprite) ) // handle what happens during a collision
        {
            // if the player is invincible or has a shield a activated, then remove the space fighter from the game
           if (player.invincible || player.power_up_counter > 0)
           {
               // incase out of bounds exception
               try
               {
                    if (space_fighters.size() > 1) space_fighters.at(index_of_current_fighter) = space_fighters.back();
                    space_fighters.pop_back();
               }
               catch (int e) {} 
           }    
        }
        index_of_current_fighter++;
    });
}
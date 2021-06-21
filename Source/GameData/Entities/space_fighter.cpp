
#include "splashkit.h"
#include "bullet.h"
#include "player.h"
#include "../lost_in_space.h"
#include "../heads_up_display.h"
#include <functional>

void add_bullet_to_space_fighter(space_fighter_data &space_fighter)
{
    int bullet_x = sprite_x (space_fighter.space_fighter_sprite);
    int bullet_y = sprite_y (space_fighter.space_fighter_sprite);
    float rotation = sprite_rotation(space_fighter.space_fighter_sprite);

    bullet space_fighter_bullet = new_bullet( bullet_x, bullet_y, rotation );
    space_fighter.bullets.push_back(space_fighter_bullet);
}

void for_all_space_fighters_bullets(vector<space_fighter_data> &space_fighters, 
    bullet_function fn)
{
    for_all_space_fighters(space_fighters, [&] (space_fighter_data &fighter) 
    {
        for (bullet bullet: fighter.bullets)
        {
            fn(bullet);
        }    
    });
}

void for_all_space_fighters_bullets_drawing(
    const vector<space_fighter_data> &space_fighters, bullet_function fn)
{
    for_all_space_fighters_drawing(space_fighters, 
        [&] (space_fighter_data &space_fighter)
    {
        for (bullet bullet: space_fighter.bullets)
        {
            fn(bullet);
        }
    });
}

void generate_space_fighter_bullets(vector<space_fighter_data> &space_fighters)
{
    static const int BULLET_COOLDOWN_IN_SECONDS = 10;
    for_all_space_fighters(space_fighters, [&] (space_fighter_data &space_fighter)
    {
        unsigned int ticks = timer_ticks( space_fighter.bullet_timer_id );
        int bullet_timer_in_seconds = get_ticks_as_seconds( ticks );

        if ( bullet_timer_in_seconds > BULLET_COOLDOWN_IN_SECONDS )
        {
            add_bullet_to_space_fighter(space_fighter);
            play_sound_effect("missle");
            reset_timer(space_fighter.bullet_timer_id);
        }
    });
}

void update_bullet_limits(vector<bullet> &bullets, bullet &bullet, int idx)
{
// check that new location is within the limits before deleting bullet
    point_2d *bullet_location = &(bullet.original_location);
    sprite *bullet_sprite = &(bullet.bullet_sprite);
    double bullet_x = (*bullet_location).x, bullet_y = (*bullet_location).y; 
    static const int RADIUS = 1000; 
    int min_x = bullet_x - RADIUS, max_x = bullet_x + RADIUS;
    int min_y = bullet_y - RADIUS, max_y = bullet_y + RADIUS;

    float x = sprite_x(*bullet_sprite);
    bool has_exceed_x = x < min_x || x  > max_x ;
    float y = sprite_y(*bullet_sprite);
    bool has_exceed_y = y < min_y || y  > max_y;

    if ( has_exceed_x || has_exceed_y )
        delete_bullet(bullets, idx);
}

void handle_space_fighter_bullet_boundaries(
    vector<space_fighter_data> &space_fighters)
{
    for_all_space_fighters(space_fighters, 
        [&] (space_fighter_data &space_fighter)
    {
        for (int idx = 0; idx < space_fighter.bullets.size(); idx++)
        {
            update_bullet_limits(space_fighter.bullets, 
                space_fighter.bullets[idx], idx);
        }
    });
}

space_fighter_data create_enemy_space_fighter(double x, double y)
{
    // Keep track of how many space fighters have spawned to make each timer unique
    static int current_fighter_id = 0; 

    space_fighter_data result;
    result.space_fighter_sprite = create_sprite ( ship_bitmap(PEGASI) ); 
    result.bullet_timer_id = "bullet_counter_" + to_string(current_fighter_id);
    result.spawn_bullet_counter = create_timer(result.bullet_timer_id);

    start_timer(result.bullet_timer_id);
    sprite_set_position(result.space_fighter_sprite, point_at(x, y));

    // Increase the fighter id to maintain a new id for the next space fighter
    current_fighter_id++; 
    return result;
}

void add_space_fighter_to_game(vector<space_fighter_data> &space_fighters, double x, double y)
{
    space_fighter_data space_fighter = create_enemy_space_fighter(x, y);
    space_fighters.push_back(space_fighter);
}

void for_all_space_fighters(vector<space_fighter_data> &space_fighters, space_fighter_function fn)
{
    for (space_fighter_data &space_fighter: space_fighters)
        fn(space_fighter);
}

void for_all_space_fighters_drawing(const vector<space_fighter_data> &space_fighters, space_fighter_function fn)
{
    for (space_fighter_data space_fighter: space_fighters)
        fn(space_fighter);
}

void draw_enemy_space_fighter(const space_fighter_data &entity)
{
    draw_sprite(entity.space_fighter_sprite);
}

void update_enemy_space_fighter(const space_fighter_data &entity)
{
    update_sprite(entity.space_fighter_sprite);
}

void for_all_space_fighters_and_player(vector<space_fighter_data> &space_fighters, player_data &player, space_fighter_and_player_function space_fighter_and_player_fn)
{
    for (space_fighter_data &space_fighter: space_fighters)
        space_fighter_and_player_fn(space_fighter, player);
}

void move_enemy_space_fighter_location_towards_player(space_fighter_data &fighter, player_data &player)
{
    static const double FIGHTER_SPEED = 0.5, MOVE_BOTTOM_LEFT = 135.0, MOVE_BOTTOM_RIGHT = 45.0, MOVE_TOP_LEFT = 225.0, MOVE_TOP_RIGHT = 315.0;
    double new_fighter_x_location = sprite_x(fighter.space_fighter_sprite);
    double new_fighter_y_location = sprite_y(fighter.space_fighter_sprite);
    bool is_player_on_left_side_of_fighter = (sprite_x(fighter.space_fighter_sprite) < sprite_x(player.player_sprite) );
    bool is_player_on_bottom_side_of_fighter = ( sprite_y(fighter.space_fighter_sprite) < sprite_y(player.player_sprite) );

    // Move the fighter towards the player and set the rotation of the fighter to face towards the player
    ( is_player_on_left_side_of_fighter ) ? new_fighter_x_location += FIGHTER_SPEED : new_fighter_x_location -= FIGHTER_SPEED;
    
    if ( is_player_on_bottom_side_of_fighter ) 
    {
        new_fighter_y_location += FIGHTER_SPEED;
        
        ( is_player_on_left_side_of_fighter ) ? sprite_set_rotation(fighter.space_fighter_sprite, MOVE_BOTTOM_RIGHT) : sprite_set_rotation(fighter.space_fighter_sprite, MOVE_BOTTOM_LEFT); 
    }  
    else
    {
        new_fighter_y_location -= FIGHTER_SPEED;
        ( is_player_on_left_side_of_fighter ) ? sprite_set_rotation(fighter.space_fighter_sprite, MOVE_TOP_RIGHT) : sprite_set_rotation(fighter.space_fighter_sprite, MOVE_TOP_LEFT); 
    }

    sprite_set_x(fighter.space_fighter_sprite, new_fighter_x_location); 
    sprite_set_y(fighter.space_fighter_sprite, new_fighter_y_location); 
}

void update_all_space_fighters(vector<space_fighter_data> &space_fighters, player_data &player)
{
    for_all_space_fighters_and_player(space_fighters, player, move_enemy_space_fighter_location_towards_player);

    for_all_space_fighters(space_fighters, update_enemy_space_fighter);

    for_all_space_fighters_bullets(space_fighters, update_bullet);
    
    for_all_space_fighters_bullets(space_fighters, update_bullet_location);
    
    generate_space_fighter_bullets(space_fighters);
  
    handle_space_fighter_bullet_boundaries(space_fighters);
}

void remove_space_fighter(vector<space_fighter_data> &space_fighters, int idx)
{
    if (space_fighters.size() > 1) 
        space_fighters.at(idx) = space_fighters.at(space_fighters.size() - 1);

    space_fighters.pop_back();
}
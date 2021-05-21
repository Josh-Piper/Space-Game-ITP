#include "splashkit.h"
#include "enemies.h"
#include "player.h"
#include "lost_in_space.h"
#include "heads_up_display.h"
#include <functional>

using std::to_string;

bullet new_bullet(double x, double y, float rotation)
{   
    float sprite_direction = rotation + 90;
    bullet result;

    result.bullet_sprite = create_sprite(bitmap_named("bullet"));
    x += (sprite_width(result.bullet_sprite) / 2);
    y -= (sprite_height(result.bullet_sprite) / 2);

    sprite_set_x(result.bullet_sprite, x);
    sprite_set_y(result.bullet_sprite, y);

    result.original_location = point_at(x, y);
    sprite_set_rotation(result.bullet_sprite, sprite_direction);
 
    return result;
}

void delete_bullet(vector<bullet> &bullets, int id)
{
    if (bullets.size() > 1) bullets.at(id) = bullets.at(bullets.size() - 1);
    bullets.pop_back();
}

void add_bullet_to_space_fighter(space_fighter_data &space_fighter)
{
    int bullet_x = sprite_x (space_fighter.space_fighter_sprite);
    int bullet_y = sprite_y (space_fighter.space_fighter_sprite);
    bullet space_fighter_bullet = new_bullet( bullet_x, bullet_y, sprite_rotation(space_fighter.space_fighter_sprite) );
    space_fighter.bullets.push_back(space_fighter_bullet);
}

space_fighter_data create_enemy_space_fighter(double x, double y)
{
    static int current_fighter_id = 0; // Keep track of how many space fighters have spawned to make each timer unique

    space_fighter_data result;
    result.space_fighter_sprite = create_sprite ( ship_bitmap(PEGASI) ); 
    result.bullet_timer_id = "bullet_counter_" + to_string(current_fighter_id);
    result.spawn_bullet_counter = create_timer(result.bullet_timer_id);

    start_timer(result.bullet_timer_id);
    sprite_set_position(result.space_fighter_sprite, point_at(x, y));

    current_fighter_id++; // Increase the fighter id to maintain a new id for the next space fighter
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

void for_all_space_fighters_bullets(vector<space_fighter_data> &space_fighters, bullet_function fn)
{
    for_all_space_fighters(space_fighters, [&] (space_fighter_data &space_fighter) 
    {
        for (bullet bullet: space_fighter.bullets)
        {
            fn(bullet);
        }    
    });
}

void for_all_space_fighters_bullets_drawing(const vector<space_fighter_data> &space_fighters, bullet_function fn)
{
    for_all_space_fighters_drawing(space_fighters, [&] (space_fighter_data &space_fighter)
    {
        for (bullet bullet: space_fighter.bullets)
        {
            fn(bullet);
        }
    });
}

void draw_bullet(const bullet &bullet)
{
    draw_sprite(bullet.bullet_sprite);
}

void update_bullet(const bullet &bullet)
{
    update_sprite(bullet.bullet_sprite);
}

void update_bullet_location(bullet &bullet)
{
    static const int SPEED_INCREMENT = 5; 
    sprite *bullet_sprite = &(bullet.bullet_sprite);
    int new_x = sprite_x(*bullet_sprite), new_y = sprite_y(*bullet_sprite);
    float sprite_direction = ( sprite_rotation(*bullet_sprite) - 90 < 0) ? 315 : sprite_rotation(*bullet_sprite) - 90;
    bool facing_towards_right_side_of_game = (sprite_direction >= 270 && sprite_direction <= 360) || (sprite_direction >= 0 && sprite_direction <= 90);
    bool facing_towards_top_half_of_game = sprite_direction >= 180 && sprite_direction <= 360;

    // Set x coordinate
    if ( facing_towards_right_side_of_game )
        new_x += SPEED_INCREMENT;
    else
        new_x -= SPEED_INCREMENT;

    // Set y coordinate
    if ( facing_towards_top_half_of_game )
        new_y -= SPEED_INCREMENT;
    else
        new_y += SPEED_INCREMENT;

    sprite_set_x(*bullet_sprite, new_x);
    sprite_set_y(*bullet_sprite, new_y);
}

void generate_space_fighter_bullets(vector<space_fighter_data> &space_fighters)
{
    static const int BULLET_COOLDOWN_IN_SECONDS = 3;
    for_all_space_fighters(space_fighters, [&] (space_fighter_data &space_fighter)
    {
        int bullet_timer_in_seconds = get_ticks_as_seconds( timer_ticks( space_fighter.bullet_timer_id ) );

        if ( bullet_timer_in_seconds > BULLET_COOLDOWN_IN_SECONDS )
        {
            add_bullet_to_space_fighter(space_fighter);
            reset_timer(space_fighter.bullet_timer_id);
        }
    });
}

void handle_space_fighter_bullet_boundaries(vector<space_fighter_data> &space_fighters)
{
    for_all_space_fighters(space_fighters, [&] (space_fighter_data &space_fighter)
    {
        for (int bullet_id = 0; bullet_id < space_fighter.bullets.size(); bullet_id++)
        {
            // check that new location is within the limits before deleting bullet
            point_2d *bullet_location = &(space_fighter.bullets[bullet_id].original_location);
            sprite *bullet_sprite = &(space_fighter.bullets[bullet_id].bullet_sprite);
            double bullet_x = (*bullet_location).x, bullet_y = (*bullet_location).y; 
            static const int RADIUS = 1000; 
            int min_x = bullet_x - RADIUS, max_x = bullet_x + RADIUS;
            int min_y = bullet_y - RADIUS, max_y = bullet_y + RADIUS;

            if (sprite_x(*bullet_sprite) < min_x || sprite_x(*bullet_sprite)  > max_x || sprite_y(*bullet_sprite)  < min_y || sprite_y(*bullet_sprite)  > max_y)
                delete_bullet(space_fighter.bullets, bullet_id);
        }
    });
}

void draw_all_enemies(const enemy_handler_data &enemies)
{
    for_all_space_fighters_drawing(enemies.space_fighters, draw_enemy_space_fighter);

    for_all_space_fighters_bullets_drawing(enemies.space_fighters, draw_bullet);
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

void update_all_enemies(enemy_handler_data &enemies, player_data &player)
{
    update_all_space_fighters(enemies.space_fighters, player);
}
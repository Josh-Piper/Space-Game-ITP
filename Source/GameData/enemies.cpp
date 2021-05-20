#include "splashkit.h"
#include "enemies.h"
#include "player.h"
#include "lost_in_space.h"
#include "heads_up_display.h"
#include <functional>

using std::to_string;

bullet new_bullet(double x, double y, int space_fighters_rotation)
{   
    int dx, dy;
    bullet result;

    result.bullet_sprite = create_sprite(bitmap_named("bullet"));
    x += (sprite_width(result.bullet_sprite) / 2);
    y -= (sprite_height(result.bullet_sprite) / 2);

    sprite_set_x(result.bullet_sprite, x);
    sprite_set_y(result.bullet_sprite, y);

    result.original_location = point_at(x, y);

    sprite_set_rotation(result.bullet_sprite, space_fighters_rotation + 90);


    // set dx - 1 if moing to the right, -1 if mving to the left
    // dy - 1 if moving down, -1 if moving towards the top
    sprite_set_dx(result.bullet_sprite, 1.0);
    sprite_set_dy(result.bullet_sprite, 1.0);

    //write_line(space_fighters_rotation);
    // 0 -> Facing directly towards the right, 
    // 90 -> Facing directly down
    // 270 -> Facing to the left
    // 360 -> Facing directly up
    

    return result;
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


void draw_all_enemies(const enemy_handler_data &enemies)
{
    for_all_space_fighters_drawing(enemies.space_fighters, draw_enemy_space_fighter);

    // Draw all bullets
    for_all_space_fighters_drawing(enemies.space_fighters, [&] (const space_fighter_data &space_fighter) 
    {
        for (bullet individual_bullet: space_fighter.bullets)
        {
            draw_sprite(individual_bullet.bullet_sprite);
        }
    });
}

void update_all_space_fighters(vector<space_fighter_data> &space_fighters, player_data &player)
{
    for_all_space_fighters_and_player(space_fighters, player, move_enemy_space_fighter_location_towards_player);

    for_all_space_fighters(space_fighters, update_enemy_space_fighter);



    for_all_space_fighters(space_fighters, [&] (space_fighter_data &space_fighter)
    {
        int bullet_timer_in_seconds = get_ticks_as_seconds( timer_ticks( space_fighter.bullet_timer_id ) );

        int x = sprite_x(space_fighter.space_fighter_sprite), y = sprite_y(space_fighter.space_fighter_sprite);
        write_line ( "Sprite Location X: " + to_string(x) + "Sprite Location Y: " + to_string(y) );
        if ( bullet_timer_in_seconds > 3 )
        {
            
            //write_line("Created a bullet");
            int x = sprite_x(space_fighter.space_fighter_sprite), y = sprite_y(space_fighter.space_fighter_sprite);
            write_line();
            write_line ( "SPRITE LOCATION X: " + to_string(x) + "SPRITE LOCATION Y: " + to_string(y) );
            write_line();   

            add_bullet_to_space_fighter(space_fighter);
            //write_line("Added bullet to space fighter, total bullets: " + to_string(space_fighter.bullets.size()));
            reset_timer(space_fighter.bullet_timer_id);
            
        }

        for (bullet individual_bullet: space_fighter.bullets)
        {
            //write_line("Looking at a bullet");
            update_sprite(individual_bullet.bullet_sprite);
        }
            
        // Implement the bullet system



        // Add and Shoot a bullet every minute or so via a counter in the space_fighter user


        // if bullet current location is outside the scope of original location +- 100 radius, then kill the bullet to prevent it from continuing forever.


        // Reset its clock every time a bulet is shot using space_fighter.bullet_timer_id
        
    });
}

void update_all_enemies(enemy_handler_data &enemies, player_data &player)
{
    update_all_space_fighters(enemies.space_fighters, player);

 
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

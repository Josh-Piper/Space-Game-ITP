#include "player.h"
#include "splashkit.h"

bitmap ship_bitmap(ship_kind kind)
{
    switch (kind)
    {
    case AQUARII:
        return bitmap_named("aquarii");
    case GLIESE:
        return bitmap_named("gliese");
    default:
        return bitmap_named("pegasi");
    }
}

player_data new_player()
{
    player_data result;
    bitmap default_bitmap = ship_bitmap(AQUARII);

    result.fuel_pct = 0.75;
    result.total_power_ups = 0;
    result.score = 0;
    result.power_up_counter = 0;
    result.invincible = false;
    result.current_power_up = bitmap_named("placeholder");

    result.player_sprite = create_sprite(default_bitmap);
    result.kind = AQUARII;

    // Position in the centre of the initial screen
    int middle = (screen_height() - (sprite_width(result.player_sprite))) / 2;
    sprite_set_x(result.player_sprite, middle);
    sprite_set_y(result.player_sprite, middle);

    return result;
}

void increment_player_power_up_count(player_data &player)
{
    player.total_power_ups++;
}

void set_player_current_power_up_image(player_data &player, bitmap new_bitmap)
{
    player.current_power_up = new_bitmap;
}

void draw_player(const player_data &player_to_draw)
{
    draw_sprite(player_to_draw.player_sprite);
}

void update_player_camera(player_data &player_to_update)
{
   // Test edge of screen boundaries to adjust the camera
    double left_edge = camera_x() + SCREEN_BORDER;
    double right_edge = left_edge + screen_width() - 2 * SCREEN_BORDER;
    double top_edge = camera_y() + SCREEN_BORDER;
    double bottom_edge = top_edge + screen_height() - 2 * SCREEN_BORDER;

    // Get the center of the player
    point_2d sprite_center = center_point(player_to_update.player_sprite);

    // Allow the game screen to follow where the player moves
    if (sprite_center.y < top_edge)
    {
        move_camera_by(0, sprite_center.y - top_edge);
    }
    else if (sprite_center.y > bottom_edge)
    {
        move_camera_by(0, sprite_center.y - bottom_edge);
    }

    // Test left/right of screen
    if (sprite_center.x < left_edge)
    {
        move_camera_by(sprite_center.x - left_edge, 0);
    }
    else if (sprite_center.x > right_edge)
    {
        move_camera_by(sprite_center.x - right_edge, 0);
    }
}

void update_fuel(double &fuel_pct)
{
    fuel_pct = fuel_pct - 1.0 / (60.0 * 50.0); // fuel will last 50 seconds
}

void update_player(player_data &player_to_update)
{
    // Apply movement based on rotation and velocity in the sprite
    update_sprite(player_to_update.player_sprite);

    update_player_camera(player_to_update);

    
    if (player_to_update.power_up_counter > 0.0) 
    {
        //counter only active when shield is accessed
        player_to_update.power_up_counter -= 1.0 / (5.0 * 60.0);
        if (player_to_update.power_up_counter < 0.0)
            player_to_update.power_up_counter = 0;
    }
    else 
    {
        if (!player_to_update.invincible) 
            update_fuel(player_to_update.fuel_pct);
            
    }

    if (player_to_update.total_power_ups >= 1000)
    {
           player_to_update.invincible = true;
    }
}

void apply_fuel_power_up_to_player(player_data &player)
{
    player.fuel_pct +=  0.20;
    if (player.fuel_pct >= 1.0) player.fuel_pct = 1.0;
    play_sound_effect("slurp");
}

void apply_shield_power_up_to_player(player_data &player)
{
    player.power_up_counter = 1.0;
    play_sound_effect("tire_puncture");
}

void apply_potion_power_up_to_player(player_data &player)
{
    player.fuel_pct -= 0.15;
    play_sound_effect("glass_ding");
   
}

void apply_drops_power_up_to_player(player_data &player)
{
    player.score += 5;
    play_sound_effect("bubble");
}

void apply_diamond_power_up_to_player(player_data &player)
{
    player.score += 50;
    play_sound_effect("balloon_pop");
}

void apply_coin_power_up_to_player(player_data &player)
{
    player.score += 1;
    play_sound_effect("pop");
}

void handle_input(player_data &player)
{
    // Handle movement - rotating left/right and moving forward/back
    sprite sprite = player.player_sprite;
    float dx = sprite_dx(sprite);
    float rotation = sprite_rotation(sprite);

    // Allow rotation with left/right keys
    if (key_down(LEFT_KEY))
        sprite_set_rotation(sprite, rotation - PLAYER_ROTATE_SPEED);
    if (key_down(RIGHT_KEY))
        sprite_set_rotation(sprite, rotation + PLAYER_ROTATE_SPEED);

    // Increase speed with up/down keys
    if (key_typed(DOWN_KEY))
        sprite_set_dx(sprite, dx - PLAYER_SPEED);
    if (key_typed(UP_KEY))
        sprite_set_dx(sprite, dx + PLAYER_SPEED);
}
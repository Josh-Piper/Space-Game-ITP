#include "splashkit.h"
#include "bullet.h"
#include "../enemies.h"
#include "../heads_up_display.h"

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

#include "splashkit.h"
#include "lost_in_space.h"
#include "player.h"
#include "power_up.h"

string get_heads_up_display_cords_as_string(point_2d cords) 
{
    string result;

    string location { point_to_string(cords) };
    location = location.substr(location.find_first_of('@') + 1);
    string x_cord { location.substr(0, 5) };
    string y_cord { location.substr(location.find_first_of(':') + 1, 5) };
    
    result += x_cord + ", ";
    result += y_cord;
    return result;
}

point_2d mini_map_coordinate(const power_up_data &power_up)
{
    //loop through and draw_pixel onto colour pixel black minimap
    //draw_pixel(clr, point2d)
}

void draw_mini_map(const vector<power_up_data> &power_ups)
{
    fill_rectangle(COLOR_BLACK, 200, 12.5, 100, 100, option_to_screen());
    return;
}

void draw_heads_up_display_background(const game_data &game) {
    clear_screen(COLOR_BLACK);
    fill_rectangle(COLOR_DARK_SLATE_GRAY, 0, 0, 325, 150, option_to_screen());

    draw_mini_map(game.power_ups);
}

void draw_heads_up_display(const game_data &game) 
{
    // Redraw everything
    static const int x_dist { 5 };
    static const int font_size { 20 };
    static const int bar_y { 110 };
    static const color text_colour { COLOR_WHITE };
    drawing_options power_up_drawing_constraints { option_to_screen() };
    power_up_drawing_constraints.scale_x = 0.35;
    power_up_drawing_constraints.scale_y = 0.35;

    draw_heads_up_display_background(game);

    draw_text("SCORE: " + to_string(game.player.score), text_colour, "hud_font", font_size, x_dist, 5, option_to_screen());
    draw_text("LOCATION: " + get_heads_up_display_cords_as_string(center_point(game.player.player_sprite)), text_colour, "hud_font", font_size, x_dist, 25, option_to_screen());
    draw_text("TOTAL POWERUPS: " + to_string(game.player.total_power_ups), text_colour, "hud_font", font_size, x_dist, 45, option_to_screen());

    draw_text("CURRENT POWERUP: ", text_colour, "hud_font", font_size, x_dist, 65, option_to_screen());
    draw_bitmap(game.player.current_power_up, 90, 25, power_up_drawing_constraints);

    /**
     * Handle drawing of the health bar
     */ 
    draw_text("HEALTH: ", text_colour, "hud_font", font_size, x_dist, 95, option_to_screen());
    draw_bitmap("empty", x_dist, bar_y, option_to_screen());
    if ( ! game.player.invincible )
        draw_bitmap("full", x_dist, 110, option_part_bmp(0, 0, (game.player.fuel_pct * bitmap_width("full")), bitmap_height("full"), option_to_screen())); 
    else 
        draw_bitmap("purple_bar", x_dist, bar_y, option_to_screen());
    
}


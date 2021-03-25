#include "splashkit.h"
#include "lost_in_space.h"
#include "player.h"
#include "power_up.h"

const int MINI_MAP_SIZE = 100;
const double MINI_MAP_X = 200.0;
const double MINI_MAP_Y = 12.5;
const double GAME_WIDTH = 3000.0;

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

point_2d mini_map_coordinate_player(double x, double y)
{
    double return_x = ( x + 1500.0 ) / GAME_WIDTH * MINI_MAP_SIZE + MINI_MAP_X;
    double return_y = ( y + 1500.0 ) / GAME_WIDTH * MINI_MAP_SIZE + MINI_MAP_Y;

    return point_at(return_x, return_y);
}

point_2d mini_map_coordinate(const power_up_data &power_up)
{
    //points escape left and top borders of the black box
    float player_x = sprite_x(power_up.power_up_sprite);
    float player_y = sprite_y(power_up.power_up_sprite);

    double return_x = ( player_x + 1500.0 ) / GAME_WIDTH * MINI_MAP_SIZE + MINI_MAP_X;
    double return_y = ( player_y + 1500.0 ) / GAME_WIDTH * MINI_MAP_SIZE + MINI_MAP_Y;

    return point_at(return_x, return_y);
}

void draw_mini_map(const vector<power_up_data> &power_ups)
{

    fill_rectangle(COLOR_BLACK, MINI_MAP_X, MINI_MAP_Y, MINI_MAP_SIZE, MINI_MAP_SIZE, option_to_screen());
    for (int i = 0; i < power_ups.size(); i++)
    {
        point_2d cords = mini_map_coordinate (power_ups[i]);
        if (cords.x >= 200 && cords.x <= 300 && cords.y >= 12.5 && cords.y <= 112.5) draw_pixel( rgba_color(199, 202, 203, 200), cords, option_to_screen() );
    }

}

void draw_heads_up_display_background(const game_data &game) {
    clear_screen(COLOR_BLACK);
    
    fill_rectangle(COLOR_DARK_SLATE_GRAY, 0, 0, 325, 150, option_to_screen());
    draw_mini_map(game.power_ups);
    //draw player
    draw_pixel( COLOR_AQUA, mini_map_coordinate_player(sprite_x(game.player.player_sprite), sprite_y(game.player.player_sprite)), option_to_screen() );
    
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


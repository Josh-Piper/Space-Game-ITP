#include "splashkit.h"
#include "lost_in_space.h"
#include "player.h"
#include "power_up.h"
#include "heads_up_display.h"

const int MINI_MAP_SIZE = 100;
const double MINI_MAP_X = 200.0; //200
const double MINI_MAP_Y = 12.5; //12.5
const double GAME_WIDTH = 3000.0; //changing the game width will make the game smaller, however, to accomodate this, you would need to move the location of the dots starting
//so it lines up with the game.
//The reason the draw_pixel leaves the screen isn't due to things spawning outside of the pixel but due to the trajectory set
//note part 1 of the game sets the velocity in part 3
const double GAME_OFFSET = 1500;
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

string append_time_suffix(string result, time_data suffix)
{
    int index = result.find(".");  
    result = result.substr(0, index + 2);
    
    switch (suffix)
    {
        case SECONDS:
            result += " seconds";
            break;
        case MINUTES:
            result += " minutes";
            break;
        case HOURS:
            result += " hours";
            break;
        default:
            break;
    }
    return result;
}
string convert_milliseconds_to_seconds(unsigned int ticks)
{
    time_data suffix = SECONDS;
    double ans = ticks / 1000.0;

    if (ans > 60 && suffix == SECONDS)
    {
        ans /= 60;
        suffix = MINUTES;
    }
    if (ans > 60 && suffix == MINUTES)
    {
        ans /= 60;
        suffix = HOURS;
    }

    return append_time_suffix( to_string(ans) , suffix);

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
    float powerup_x = sprite_x(power_up.power_up_sprite);
    float powerup_y = sprite_y(power_up.power_up_sprite);

    double return_x = ( powerup_x + GAME_OFFSET ) / GAME_WIDTH * MINI_MAP_SIZE + MINI_MAP_X;
    double return_y = ( powerup_y + GAME_OFFSET ) / GAME_WIDTH * MINI_MAP_SIZE + MINI_MAP_Y;

    return point_at(return_x, return_y);
}

void draw_mini_map(const vector<power_up_data> &power_ups, const player_data &player)
{

    fill_rectangle(COLOR_BLACK, MINI_MAP_X, MINI_MAP_Y, MINI_MAP_SIZE, MINI_MAP_SIZE, option_to_screen());

    for (int i = 0; i < power_ups.size(); i++)
    {
        point_2d cords = mini_map_coordinate (power_ups[i]);
        if (cords.x >= 200 && cords.x <= 300 && cords.y >= 12.5 && cords.y <= 112.5) draw_pixel( rgba_color(199, 202, 203, 200), cords, option_to_screen() );
    }

    //draw player
    point_2d player_loca = mini_map_coordinate_player(sprite_x(player.player_sprite), sprite_y(player.player_sprite));
    if (player_loca.x >= 200 && player_loca.x <= 300 && player_loca.y >= 12.5 && player_loca.y <= 112.5)  draw_pixel( COLOR_AQUA, player_loca, option_to_screen() );

}

void draw_heads_up_display_background(const game_data &game) {
    clear_screen(COLOR_BLACK);
    
    fill_rectangle(COLOR_DARK_SLATE_GRAY, 0, 0, 325, 175, option_to_screen());
    draw_mini_map(game.power_ups, game.player);
}

void draw_heads_up_display(const game_data &game) 
{
    // Redraw everything
    static const int x_dist { 5 };
    static const int font_size { 20 };
    static const int bar_y { 110 };
    static const string font { "hud_font" };
    static const color text_colour { COLOR_WHITE };
    drawing_options power_up_drawing_constraints { option_to_screen() };
    power_up_drawing_constraints.scale_x = 0.35;
    power_up_drawing_constraints.scale_y = 0.35;

    draw_heads_up_display_background(game);

    draw_text("SCORE: " + to_string(game.player.score), text_colour, font, font_size, x_dist, 5, option_to_screen());
    draw_text("LOCATION: " + get_heads_up_display_cords_as_string(center_point(game.player.player_sprite)), text_colour, font, font_size, x_dist, 25, option_to_screen());
    draw_text("TOTAL POWERUPS: " + to_string(game.player.total_power_ups), text_colour, font, font_size, x_dist, 45, option_to_screen());

    draw_text("CURRENT POWERUP: ", text_colour, font, font_size, x_dist, 65, option_to_screen());
    draw_bitmap(game.player.current_power_up, 90, 25, power_up_drawing_constraints);

    string time_played = convert_milliseconds_to_seconds(timer_ticks( game.game_timer));
    draw_text("TIME PLAYED: " + time_played, text_colour, font, font_size, x_dist, 152, option_to_screen() );

    /**
     * Handle drawing of the health bar
     */ 
    draw_text("HEALTH: ", text_colour, font, font_size, x_dist, 95, option_to_screen());
    draw_bitmap("empty", x_dist, bar_y, option_to_screen());
    if ( ! game.player.invincible )
        draw_bitmap("full", x_dist, 110, option_part_bmp(0, 0, (game.player.fuel_pct * bitmap_width("full")), bitmap_height("full"), option_to_screen())); 
    else 
        draw_bitmap("purple_bar", x_dist, bar_y, option_to_screen());
    
}


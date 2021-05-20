#include "splashkit.h"
#include "lost_in_space.h"
#include "player.h"
#include "power_up.h"
#include "heads_up_display.h"

const int MINI_MAP_SIZE = 100;
const double MINI_MAP_X = 200.0; 
const double MINI_MAP_Y = 12.5; 
const double GAME_WIDTH = 3000.0; 
const double GAME_OFFSET = 1500;

string remove_cords_prefix_filler_text(string cords)
{
    return cords.substr(cords.find_first_of('@') + 1);
}

string get_heads_up_display_cords_as_string(point_2d cords) 
{
    static const int INDEX_OF_BEGIN_NUMBER = 0, INDEX_OF_END_NUMBER = 5;
    string result;

    // Change the format of a cord @pt ... some number: somenumber to somenumber , somenumber
    string player_current_location = remove_cords_prefix_filler_text( point_to_string(cords) );
    string x_cord { player_current_location.substr(INDEX_OF_BEGIN_NUMBER, INDEX_OF_END_NUMBER) };
    string y_cord { player_current_location.substr(player_current_location.find_first_of(':') + 1, INDEX_OF_END_NUMBER) };
    
    result += x_cord + ", ";
    result += y_cord;
    return result;
}

string convert_number_to_two_dp(string number)
{
    int index = number.find(".");  
    return number.substr(0, index + 2); 
}

string append_time_suffix(string current_time, time_data suffix)
{
    string result = convert_number_to_two_dp(current_time);
    
    // Append the time suffix to a string 
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

double get_ticks_as_seconds(unsigned int ticks)
{
    return ticks / 1000.0;
}

string convert_milliseconds_to_seconds(unsigned int ticks)
{
    static const int TIME_CONVERSION_RATE = 60;
    time_data suffix = SECONDS;
    double ans = get_ticks_as_seconds(ticks); 

    // Convert milliseconds to its current responding time whether seconds, minutes or hours. 
    if (ans > TIME_CONVERSION_RATE && suffix == SECONDS)
    {
        ans /= TIME_CONVERSION_RATE;
        suffix = MINUTES;
    }
    if (ans > TIME_CONVERSION_RATE && suffix == MINUTES)
    {
        ans /= TIME_CONVERSION_RATE;
        suffix = HOURS;
    }

    return append_time_suffix( to_string(ans) , suffix);
}

point_2d mini_map_coordinate_player(double x, double y)
{
    // Return the coordinate of a player according to their location in the game
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

    for (int powerup = 0; powerup < power_ups.size(); powerup++)
    {
        point_2d cords = mini_map_coordinate (power_ups[powerup]);
        if (cords.x >= 200 && cords.x <= 300 && cords.y >= 12.5 && cords.y <= 112.5) draw_pixel( rgba_color(199, 202, 203, 200), cords, option_to_screen() );
    }

    //draw player
    point_2d player_location = mini_map_coordinate_player(sprite_x(player.player_sprite), sprite_y(player.player_sprite));
    if (player_location.x >= 200 && player_location.x <= 300 && player_location.y >= 12.5 && player_location.y <= 112.5)  draw_pixel( COLOR_AQUA, player_location, option_to_screen() );

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
    draw_text("CURRENT LEVEL: " + to_string(game.game_level), text_colour, font, font_size, x_dist, 25, option_to_screen());
    draw_text("LOCATION: " + get_heads_up_display_cords_as_string(center_point(game.player.player_sprite)), text_colour, font, font_size, x_dist, 45, option_to_screen());
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


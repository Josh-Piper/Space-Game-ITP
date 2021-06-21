#include "splashkit.h"
#include "lost_in_space.h"
#include "heads_up_display.h"
#include "./Entities/player.h"
#include "./Entities/power_up.h"
#include "./Entities/space_fighter.h"

const int MINI_MAP_SIZE = 100;
const int MINI_MAP_X_END = 300;
const double MINI_MAP_X = 200.0; 
const double MINI_MAP_Y = 12.5; 
const double MINI_MAP_Y_END = 112.5;
const double GAME_WIDTH = 3000.0; 
const double GAME_OFFSET = 1500;

string remove_cords_prefix_filler_text(string cords)
{
    return cords.substr(cords.find_first_of('@') + 1);
}

string get_heads_up_display_cords_as_string(point_2d cords) 
{
    static const int START_IDX = 0, END_IDX = 5;
    string new_cords = point_to_string(cords), player_current_location, result;

    // Change the format of a cord @pt ... x : y to x, y
    player_current_location = remove_cords_prefix_filler_text( new_cords );
    string x_cord { player_current_location.substr( START_IDX, END_IDX ) };

    int y_start_idx = player_current_location.find_first_of(':') + 1;
    string y_cord { player_current_location.substr( y_start_idx, END_IDX ) };
    
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

    double return_x = ( powerup_x + GAME_OFFSET ) / GAME_WIDTH * MINI_MAP_SIZE
     + MINI_MAP_X;
    double return_y = ( powerup_y + GAME_OFFSET ) / GAME_WIDTH * MINI_MAP_SIZE
     + MINI_MAP_Y;

    return point_at(return_x, return_y);
}

point_2d mini_map_coordinate(const space_fighter_data &space_fighter)
{
    //points escape left and top borders of the black box
    float powerup_x = sprite_x(space_fighter.space_fighter_sprite);
    float powerup_y = sprite_y(space_fighter.space_fighter_sprite);

    double return_x = ( powerup_x + GAME_OFFSET ) / GAME_WIDTH * MINI_MAP_SIZE 
     + MINI_MAP_X;
    double return_y = ( powerup_y + GAME_OFFSET ) / GAME_WIDTH * MINI_MAP_SIZE
     + MINI_MAP_Y;

    return point_at(return_x, return_y);
}

bool is_mini_map_position_within_mini_map_bounds(point_2d cords)
{
    return (cords.x >= MINI_MAP_X && cords.x <= MINI_MAP_X_END &&
            cords.y >= MINI_MAP_Y && cords.y <= MINI_MAP_Y_END);
}

void draw_mini_map_location_for_powerups(const vector<power_up_data> &power_ups)
{
    const color GRAY_CLR = rgba_color(199, 202, 203, 200);
    for (int powerup = 0; powerup < power_ups.size(); powerup++)
    {
        point_2d cords = mini_map_coordinate ( power_ups[powerup] );
        if (is_mini_map_position_within_mini_map_bounds( cords) ) 
            draw_pixel( GRAY_CLR, cords, option_to_screen() );
    }
}

void draw_mini_map_location_for_space_fighters
    (const vector<space_fighter_data> space_fighters)
{
    point_2d cords;

    for (space_fighter_data space_fighter: space_fighters)
    {   
        cords = mini_map_coordinate ( space_fighter );
        if (is_mini_map_position_within_mini_map_bounds( cords) ) 
            draw_pixel( COLOR_RED, cords, option_to_screen() );
    }
}

void draw_mini_map_location_for_player(const player_data &player)
{
    point_2d player_location;
    float player_x = sprite_x(player.player_sprite);
    float player_y = sprite_y(player.player_sprite);

    player_location = mini_map_coordinate_player( player_x, player_y );
    if (is_mini_map_position_within_mini_map_bounds(player_location)) 
        draw_pixel( COLOR_AQUA, player_location, option_to_screen() );
}

void draw_mini_map(const vector<power_up_data> &power_ups, 
    const player_data &player, const enemy_handler_data &enemies)
{
    // Draw the minimap background
    fill_rectangle(COLOR_BLACK, MINI_MAP_X, MINI_MAP_Y, MINI_MAP_SIZE, 
        MINI_MAP_SIZE, option_to_screen()); 

    draw_mini_map_location_for_powerups( power_ups );
    draw_mini_map_location_for_space_fighters( enemies.space_fighters );
    draw_mini_map_location_for_player( player );
}

void draw_heads_up_display_background(const game_data &game) {
    clear_screen(COLOR_BLACK);
    fill_rectangle(COLOR_DARK_SLATE_GRAY, 0, 0, 325, 175, option_to_screen());
}

void draw_heads_up_display(const game_data &game) 
{
    // Redraw everything
    static const int x_dist { 5 };
    static const int font_size { 20 };
    static const int bar_y { 110 };
    static const string font { "hud_font" };
    static const color text_colour { COLOR_WHITE };
    drawing_options opts { option_to_screen() };
    drawing_options power_up_drawing_constraints { option_to_screen() };
    power_up_drawing_constraints.scale_x = 0.35;
    power_up_drawing_constraints.scale_y = 0.35;

    string time_played = convert_milliseconds_to_seconds
        (timer_ticks( game.game_timer));
    string location =  get_heads_up_display_cords_as_string
        (center_point(game.player.player_sprite));

    draw_heads_up_display_background(game);

    draw_mini_map(game.power_ups, game.player, game.enemies);

    draw_text("SCORE: " + to_string(game.player.score), text_colour, font, 
        font_size, x_dist, 5, opts);

    draw_text("CURRENT LEVEL: " + to_string(game.game_level), text_colour, 
        font, font_size, x_dist, 25, opts);

    draw_text("LOCATION: " + location, text_colour, font, font_size, 
        x_dist, 45, opts);

    draw_text("CURRENT POWERUP: ", text_colour, font, font_size, x_dist, 
        65, opts);

    draw_bitmap(game.player.current_power_up, 90, 25, 
        power_up_drawing_constraints);

    draw_text("TIME PLAYED: " + time_played, text_colour, font, font_size, 
        x_dist, 152, opts );

    draw_text("HEALTH: ", text_colour, font, font_size, x_dist, 95, opts);
    draw_bitmap("empty", x_dist, bar_y, opts);

    if ( ! game.player.invincible )
    {
        double health_bar_ratio = (game.player.fuel_pct * bitmap_width("full"));
        drawing_options health_bar_limits = option_part_bmp (0, 0,
            health_bar_ratio, bitmap_height("full"), opts);

        draw_bitmap("full", x_dist, 110, health_bar_limits); 
    }
    else
    { 
        draw_bitmap("purple_bar", x_dist, bar_y, opts);
    }
    
}
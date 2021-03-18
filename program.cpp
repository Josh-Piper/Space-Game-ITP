#include "./include/splashkit/splashkit.h"
#include "player.h"
#include "power_up.h"

/**
 * Load the game images, sounds, etc.
 */
void load_resources()
{
    load_resource_bundle("game_bundle", "lost_in_space.txt");
}

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

void draw_heads_up_display(const player_data &player) 
{
    // Redraw everything
    static const int x_dist { 5 };
    static const int font_size { 20 };
    static const int bar_y { 110 };
    

    clear_screen(COLOR_BLACK);

    fill_rectangle(COLOR_DARK_SLATE_GRAY, 0, 0, 325, 150, option_to_screen());
    fill_rectangle(COLOR_BLACK, 200, 12.5, 100, 100, option_to_screen());

    draw_text("SCORE: " + player.score, COLOR_WHITE, "hud_font", font_size, x_dist, 5, option_to_screen());
    draw_text("LOCATION: " + get_heads_up_display_cords_as_string(center_point(player.player_sprite)), COLOR_WHITE, "hud_font", font_size, x_dist, 25, option_to_screen());
    draw_text("TOTAL POWERUPS: ", COLOR_WHITE, "hud_font", font_size, x_dist, 45, option_to_screen());
    draw_text("CURRENT POWERUP: ", COLOR_WHITE, "hud_font", font_size, x_dist, 65, option_to_screen());
    draw_text("HEALTH: ", COLOR_WHITE, "hud_font", font_size, x_dist, 95, option_to_screen());
    draw_bitmap("empty", x_dist, bar_y, option_to_screen());
    draw_bitmap("full", x_dist, 110, option_part_bmp(0, 0, (player.fuel_pct * bitmap_width("full")), bitmap_height("full"), option_to_screen())); 
    
}

/**
 * Entry point.
 * 
 * Manages the initialisation of data, the event loop, and quitting.
 */
int main()
{
    open_window("Lost In Space", 800, 800);
    load_resources();

    player_data player;
    power_up_data power_up;

    player = new_player();
    power_up = new_power_up(550, 550);

    while ( ! quit_requested() )
    {
        // Handle input to adjust player movement
        process_events();
        handle_input(player);

        // Perform movement and update the camera
        update_player(player);
        update_power_up(power_up);

        draw_heads_up_display(player);
        // as well as the player who can move
        draw_player(player);
        draw_power_up(power_up);

        refresh_screen(60);
    }

    return 0;
}
#include "./include/splashkit/splashkit.h"
#include "player.h"
#include "power_up.h"
#include "lost_in_space.h"
#include "heads_up_display.h"

/**
 * Load the game images, sounds, etc.
 */

using std::to_string;


/**
 * Entry point.
 * 
 * Manages the initialisation of data, the event loop, and quitting.
 */


void handle_game()
{
    game_data game { new_game() };

    while ( ! quit_requested() )
    {
        process_events();

        handle_input(game.player);
        update_game(game);
        draw_game(game);
        //if something break out of loop
    }
}

void load_menu_resources()
{
    // Home Screen
    load_bitmap("home_screen", "home_screen.png");
    //settings
    load_bitmap("default_settings_button", "default_settings_button.png");
    load_bitmap("highlighted_settings_button", "highlighted_settings_button.png");
    //play
    load_bitmap("default_play_game_button", "default_play_game_button.png");
    load_bitmap("highlighted_play_game_button", "highlighted_play_game_button.png");
    //lb
    load_bitmap("default_leaderboard_button", "default_leaderboard_button.png");
    load_bitmap("highlighted_leaderboard_button", "highlighted_leaderboard_button.png");
    //info
    load_bitmap("default_information_button", "default_information_button.png");
    load_bitmap("highlighted_information_button", "highlighted_information_button.png");
   

}

 
enum game_state { HOME_SCREEN, PLAY_GAME_SCREEN, SETTINGS_SCREEN, INFORMATION_SCREEN };
enum highlighted_button_state { NONE, FIRST, SECOND, THIRD, FOURTH };

struct music_handler_data
{
    string          current_song;
    float           current_volume;
    bool            changed_volume_required;
    bool            is_muted;
} ;

bool is_increase_new_volume_valid(float volume) { return ((volume += 0.1) <= 1.1); };

bool is_decrease_new_volume_valid(float volume) { return ((volume -= 0.1) >= 0.0); }

void increase_volume(music_handler_data &music_player) { if (is_increase_new_volume_valid(music_player.current_volume)) music_player.current_volume += 0.1; }

void decrease_volume(music_handler_data &music_player) { if (is_decrease_new_volume_valid(music_player.current_volume)) music_player.current_volume -= 0.1; }

std::string get_current_volume_as_percentage(music_handler_data &music_player) 
{
    string str { std::to_string(music_player.current_volume).substr(0, 3) };
    if (str == "1.0") return "100%";
    if (str == "0.0") return "0%";
    return str.substr(2, 1).append("0%");
}

music_handler_data create_music_handler()
{
    music_handler_data result;
    //result.current_song = "music0";
    result.current_volume = 0.5f;
    result.changed_volume_required = false;
    result.is_muted = false;
    return result;
}

struct menu_handler_data
{
    game_state                      game_state;
    highlighted_button_state        highlighted_button;
    music_handler_data              music_player;
};

menu_handler_data create_menu_handler()
{
    menu_handler_data result;
    result.game_state = HOME_SCREEN;
    result.highlighted_button = NONE;
    result.music_player = create_music_handler();
    return result;
}

void append_vector_menu_buttons_to_highlight(const menu_handler_data &global_game_settings, std::vector<string> &menu) 
{
    if (global_game_settings.highlighted_button != NONE) 
    {
        menu[global_game_settings.highlighted_button].erase(0,7);
        menu[global_game_settings.highlighted_button].insert(0, "highlighted");
    }
}

void draw_menu(const vector<string> menu) 
{
    draw_bitmap(menu.at(0), 0, 0);
    
    int x_location { 100 }, y_location { 165 };

    if (menu.size() > 1) 
    {
        for (int i = 1; i < menu.size(); i++) 
        {
            //if there are two rows, then reset the values to draw the next row
            if (i == 3) 
            {
                x_location -= 690;
                y_location += 315;
            }

            draw_bitmap(menu.at(i), x_location, y_location);
            x_location += 345;
            
        }
    }
}


void draw_home_screen_background(const menu_handler_data &global_game_settings) 
{
    std::vector<string> home_screen_buttons 
    {
        "home_screen", "default_play_game_button", "default_leaderboard_button", "default_settings_button", "default_information_button"
    };

    // append_vector_menu_buttons_to_highlight(global_game_settings, home_screen_buttons);

    draw_menu(home_screen_buttons);
}



void handle_menu()
{
    menu_handler_data global_menu_handler = create_menu_handler();

    while ( ! quit_requested() )
    {
        clear_screen();
        
        draw_home_screen_background(global_menu_handler);
        process_events();

        
        refresh_screen();

    }
}

int main()
{
    open_window("Lost In Space", 800, 800);
    //load_resources();

    load_menu_resources();

    
    handle_menu();

    return 0;
}
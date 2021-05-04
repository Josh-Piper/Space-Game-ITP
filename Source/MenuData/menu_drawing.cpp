#include "splashkit.h"
#include "menu.h"
#include "../../Source/Utilities/leaderboard.h"
#include <vector>

void append_vector_menu_buttons_to_highlight(const menu_handler_data &global_game_settings, std::vector<string> &menu) 
{
    highlighted_button_state button = global_game_settings.highlighted_button;
    // Append the highlighted button id only when a button is hovered over
    if (button != NONE) 
    {
        menu[button].erase(0,7);
        menu[button].insert(0, "highlighted");
    }
}

void draw_menu(const vector<string> menu) 
{
    draw_bitmap(menu.at(0), 0, 0, option_to_screen());

    // start location for x,y of the first button.
    int x_location { 101 }, y_location { 165 };

    if (menu.size() > 1) 
    {
        for (int button = 1; button < menu.size(); button++) 
        {
            //if you create three buttons, then create a new row. As each row has two columns.
            if (button == 3) 
            {
                x_location -= 690;
                y_location += 315;
            }

            draw_bitmap(menu.at(button), x_location, y_location, option_to_screen());
            x_location += 345;
            
        }
    }
}

void draw_text_after_two_buttons(vector<string> reading_file)
{
    static const string font { "hud_font" };
    static const int margin = 10; 
    int start_y_location = 450, start_x_location = 25, font_size = INT_MAX;
    int possible_size = font_size = 2000 / reading_file[1].length();
    // Set the font size to 50 if there are more than 5 lines, to have a base size if the file is large
    if (reading_file.size() > 5) font_size = 50;

    // Set the font size according to the first lines length
    if (reading_file.size() > 1) {
        // Only change it if the size in regards to the length is smaller than the current font size
        if (possible_size < font_size) font_size = possible_size;
    } 
    else{ font_size = 100 ;} // If no font size has been set, set it to 100 

    // Print all the lines within the file
    for (string text: reading_file)
    {
        draw_text(text, COLOR_WHITE_SMOKE, font, font_size, start_x_location, start_y_location, option_to_screen());
        start_y_location += font_size + margin;
    }
}

void draw_home_screen_background(const menu_handler_data &global_game_settings) 
{
    std::vector<string> home_screen_buttons 
    {
        "home_screen", "default_play_game_button", "default_leaderboard_button", "default_settings_button", "default_information_button"
    };

    append_vector_menu_buttons_to_highlight(global_game_settings, home_screen_buttons);

    draw_menu(home_screen_buttons);
}

void draw_information_screen_background(const menu_handler_data &global_game_settings) 
{
    std::vector<string> information_screen_buttons 
    {
        "information_screen", "default_home_button", "default_repo_button"
    };

    append_vector_menu_buttons_to_highlight(global_game_settings, information_screen_buttons);

    draw_menu(information_screen_buttons);
    
    //Draw the information section from the information.txt file
    vector<string> information_file = read_information_text();
    draw_text_after_two_buttons(information_file);
}

void draw_leader_screen_background(const menu_handler_data &global_game_settings) 
{
    std::vector<string> information_screen_buttons 
    {
        "leaderboard_screen", "default_home_button", "default_clear_leaderboard_button"
    };

    append_vector_menu_buttons_to_highlight(global_game_settings, information_screen_buttons);

    draw_menu(information_screen_buttons);

    // Read the leaderboard details
    vector<string> leaderboard_file = read_leaderboard_text();
    draw_text_after_two_buttons(leaderboard_file);
}

void draw_settings_screen_background(menu_handler_data &global_menu_handler) 
{
    std::vector<string> settings_screen_buttons 
    {
        "settings_screen", "default_home_button"
    };
    (global_menu_handler.music_player.is_muted) ? settings_screen_buttons.push_back("default_unmute_button") : settings_screen_buttons.push_back("default_mute_button");
    settings_screen_buttons.push_back("default_volume_down");
    settings_screen_buttons.push_back("default_volume_up");

    append_vector_menu_buttons_to_highlight(global_menu_handler, settings_screen_buttons);

    draw_menu(settings_screen_buttons);
}

void draw_settings_paused_screen_background(menu_handler_data &global_menu_handler) 
{
    std::vector<string> information_screen_buttons 
    {
    "paused_screen", "default_return_to_game_button", "default_home_button"
    };

    append_vector_menu_buttons_to_highlight(global_menu_handler, information_screen_buttons);

    draw_menu(information_screen_buttons);
}

vector<string> form_paused_menu_information(game_data &game)
{
    vector<string> result;
    result.push_back("Player Information");
    result.push_back("Your Current Score is: " + to_string(game.player.score) );
    return result;
}

void draw_end_game_screen_background(menu_handler_data &global_menu_handler, int score)
{
    std::vector<string> information_screen_buttons 
    {
    "ending_screen", "default_home_button", "default_save_button"
    };

    append_vector_menu_buttons_to_highlight(global_menu_handler, information_screen_buttons);

    draw_menu(information_screen_buttons);

    vector<string> end_messages {
        "Is this a High Score?",
        "Click Save to submit your Score to the Leaderboards",
        "Your Score Was: " + to_string(score)
    };

    draw_text_after_two_buttons(end_messages);
}
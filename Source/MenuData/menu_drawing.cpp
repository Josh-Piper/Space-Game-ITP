#include "splashkit.h"
#include "menu_logic.h"
#include "menu_utilities.h"
#include "../../Source/Utilities/leaderboard.h"
#include <vector>
#include <map>

void append_vector_menu_buttons_to_highlight(
    const menu_handler_data &global_game_settings, std::vector<string> &menu) 
{
    static const int FIRST_INDEX = 0;
    static const int LAST_INDEX = 7;
    highlighted_button_state button = global_game_settings.highlighted_button;

    if (button != NONE) 
    {
        menu[button].erase(FIRST_INDEX, LAST_INDEX);
        menu[button].insert(FIRST_INDEX, "highlighted");
    }
}

void draw_menu(const vector<string> menu) 
{
    static const int IMAGE_INDEX = 0, IMAGE_LOCA = 0;
    drawing_options opts = option_to_screen();

    draw_bitmap(menu.at(IMAGE_INDEX), IMAGE_LOCA, IMAGE_LOCA, opts);
    int x_location { 101 }, y_location { 165 };

    if (menu.size() > 1) 
    {
        for (int button_idx = 1; button_idx < menu.size(); button_idx++) 
        {
            //if you create three buttons, then create a new row. 
            if (button_idx == 3) 
            {
                x_location -= 690;
                y_location += 315;
            }

            draw_bitmap(menu.at(button_idx), x_location, y_location, opts);
            // move across to the right for the next button
            x_location += 345; 
        }
    }
}

void draw_text_after_two_buttons(vector<string> file_to_read)
{
    static const string font { "hud_font" };
    static const int margin = 10; 
    static const color clr = COLOR_WHITE_SMOKE;
    drawing_options opts = option_to_screen();

    int start_y = 450, start_x = 25, font_size = 
        font_size_depending_on_files_info(file_to_read);

    for (string text: file_to_read)
    {
        draw_text(text, clr, font, font_size, start_x, start_y, opts);
        start_y += font_size + margin;
    }
}

void draw_home_screen_background(const menu_handler_data &global_game_settings) 
{
    std::vector<string> home_screen_buttons 
    {
        "home_screen", 
        "default_play_game_button", 
        "default_leaderboard_button", 
        "default_settings_button", 
        "default_information_button"
    };

    append_vector_menu_buttons_to_highlight(
        global_game_settings, home_screen_buttons);

    draw_menu(home_screen_buttons);
}

void draw_information_screen_background(
    const menu_handler_data &global_game_settings) 
{
    std::vector<string> information_screen_buttons 
    {
        "information_screen", "default_home_button", "default_repo_button"
    };

    append_vector_menu_buttons_to_highlight(
        global_game_settings, information_screen_buttons);

    draw_menu(information_screen_buttons);

    vector<string> information_file = read_information_file();
    draw_text_after_two_buttons(information_file);
}

void draw_leaderboard_sorting_button(sort_type sorting_method)
{
    static const string SORTING_BUTTON_BITMAP = "default_sorting_button";
    static const color SORTING_BUTTON_COLOR = COLOR_BEIGE;
    static const font SORTING_BUTTON_FONT = font_named("Audacity");
    static const int button_x = 560, button_y = 730, font_size = 20;

    static const std::map<sort_type, string> draw_sort 
    {
        { ALPHA_ASCENDING, "Alpha Ascending" },
        { ALPHA_DESCENDING, "Alpha Descending" },
        { DATE_ASCENDING, "Date Ascending" },
        { DATE_DESCENDING, "Data Descending" },
        { SCORE_ASCENDING, "Score Ascending" },
        { SCORE_DESCENDING, "Score Descending" }
    };

    vector<leaderboard_entry_data> leaderboard = 
        create_leaderboard_vector_from_file(); 

    return_leaderboard_sorted(leaderboard, sorting_method); 
    
    vector<string> leaderboard_entries = 
        convert_leaderboard_entry_vector_to_string_vector(leaderboard);

    draw_text_after_two_buttons(leaderboard_entries); 

    draw_bitmap(SORTING_BUTTON_BITMAP, button_x, button_y, option_to_screen());

    draw_text(draw_sort.at(sorting_method), SORTING_BUTTON_COLOR, 
        SORTING_BUTTON_FONT, font_size, button_x + 90, button_y + 18, 
        option_to_screen());
}

void draw_leaderboard_screen_background(
    const menu_handler_data &global_game_settings) 
{    
    std::vector<string> information_screen_buttons 
    {
        "leaderboard_screen", 
        "default_home_button", 
        "default_clear_leaderboard_button"
    };

    append_vector_menu_buttons_to_highlight(global_game_settings, 
        information_screen_buttons);

    draw_menu(information_screen_buttons);

    draw_leaderboard_sorting_button(
        global_game_settings.leaderboard_sorting_method);
}

void draw_settings_screen_background(menu_handler_data &global_menu_handler) 
{
    std::vector<string> settings_screen_buttons 
    {
        "settings_screen", "default_home_button"
    };

    if (global_menu_handler.music_player.is_muted)
        settings_screen_buttons.push_back("default_unmute_button");
    else
        settings_screen_buttons.push_back("default_mute_button");

    settings_screen_buttons.push_back("default_volume_down");
    settings_screen_buttons.push_back("default_volume_up");

    append_vector_menu_buttons_to_highlight(global_menu_handler, 
        settings_screen_buttons);

    draw_menu(settings_screen_buttons);
}

void draw_settings_paused_screen_background(
    menu_handler_data &global_menu_handler) 
{
    std::vector<string> information_screen_buttons 
    {
    "paused_screen", "default_return_to_game_button", "default_home_button"
    };

    append_vector_menu_buttons_to_highlight(global_menu_handler, 
        information_screen_buttons);

    draw_menu(information_screen_buttons);
}

vector<string> form_paused_menu_information(game_data &game) 
{
    vector<string> result;
    result.push_back("Player Information");
    result.push_back("Your Current Score is: " + to_string(game.player.score) );
    return result;
}

string get_end_message_from_level(int level)
{
    static const std::map<int, string> level_message 
    {
        { 1, "Keep Trying! - You're Getting Better" },
        { 2, "Good Job! Improving Already" },
        { 3, "Excellent... Its Getting Tough" },
        { 4, "Impressive, Are You Elon Musk?" },
        { 5, "Uncharted Territory is Dangerous... Be Careful Next Time" },
        { 6, "I Almost Thought You Were An Alien... Great Job" },
        { 7, "Wow... What Did You Do To Annoy the Aliens" },
        { 8, "Excellent Work Soldier" },
        { 9, "You Might Just Be the Best At This" },
        { 10, "You Almost Died as a Legend" },
        { 11, "You're Renown Amounst the Galaxy... Truly An Unfortunate Death" }
    };

    // Return the message dependent on the level
    auto result = level_message.find(level);
    if (result != level_message.end())
    {
        return result->second;
    }
    
    return "They Call You... A Legend Amounst Legends...";
}

void insert_end_game_messages(vector<string> &vec)
{
    vec.push_back("Is this your Highest Score?");
    vec.push_back("Click Save to submit your Score to the Leaderboards");
}

void draw_end_game_screen_background(menu_handler_data &global_menu_handler, 
    int score, int level)
{
    vector<string> information_screen_buttons 
    {
        "ending_screen", "default_home_button", "default_save_button" 
    }, end_messages;

    append_vector_menu_buttons_to_highlight(global_menu_handler, 
        information_screen_buttons);

    draw_menu(information_screen_buttons);

    end_messages.push_back(get_end_message_from_level(level));
    insert_end_game_messages(end_messages);
    end_messages.push_back("Your Score Was: " + to_string(score));

    draw_text_after_two_buttons(end_messages);
}
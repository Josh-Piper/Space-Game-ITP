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
    
    //music
    load_music("music1", "music_ghost_beats.mp3");
    load_music("music2", "music_last_but_not_least.mp3");
    load_music("music3", "music_sam_barsh.mp3");
    load_music("music4", "music_spaceless_needle.mp3");
    load_music("music5", "music_sunkissed_remix.mp3");


    // Settings Screen
    load_bitmap("settings_screen", "settings_screen.png");
    load_bitmap("default_home_button", "default_home_button.png");
    load_bitmap("highlighted_home_button", "highlighted_home_button.png");
    load_bitmap("default_mute_button", "default_mute_button.png");
    load_bitmap("highlighted_mute_button", "highlighted_mute_button.png");
    load_bitmap("default_unmute_button", "default_unmute_button.png");
    load_bitmap("highlighted_unmute_button", "highlighted_unmute_button.png");
    load_bitmap("default_volume_down", "default_volume_down.png");
    load_bitmap("highlighted_volume_down", "highlighted_volume_down.png");
    load_bitmap("default_volume_up", "default_volume_up.png");
    load_bitmap("highlighted_volume_up", "highlighted_volume_up.png");

}

 
enum game_state { HOME_SCREEN, PLAY_GAME_SCREEN, LEADERBOARD_SCREEN, SETTINGS_SCREEN, INFORMATION_SCREEN };
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
    result.current_song = "music0";
    result.current_volume = 0.5f;
    result.changed_volume_required = false;
    result.is_muted = false;
    return result;
}


int get_next_song_number(string original_number) 
{
    int number {std::stoi(original_number)};    
    int return_number {};
    (number + 1 < 5) ? return_number = number + 1 : return_number = 0;
    return return_number;
}


string return_next_song(string current_song) 
{
    string current_number {current_song.substr(current_song.length() - 1, 1)};
    string new_number {std::to_string(get_next_song_number(current_number))};
    return current_song.substr(0, current_song.length() - 1).append(new_number);
}



void handle_music(music_handler_data &music_handler) 
{
 
    if ( ! music_playing() ) 
    {
        music_handler.current_song = return_next_song(music_handler.current_song);
        fade_music_in(music_handler.current_song, 3000);
        set_music_volume(music_handler.current_volume);
    }

    if (music_handler.changed_volume_required) set_music_volume(music_handler.current_volume);

    (music_handler.is_muted) ? pause_music() : resume_music();
    

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
    
    int x_location { 101 }, y_location { 165 };

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

    append_vector_menu_buttons_to_highlight(global_game_settings, home_screen_buttons);

    draw_menu(home_screen_buttons);
}


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

bool is_mouse_between_two_points(int first_x, int first_y, int second_x, int second_y) 
{
    return ((mouse_x() >= first_x && mouse_x() <= second_x) && (mouse_y() >= first_y && mouse_y() <= second_y));
}

bool is_mouse_in_first_button() { return (is_mouse_between_two_points(100, 165, 350, 415)); }

bool is_mouse_in_second_button() { return (is_mouse_between_two_points(445, 165, 695, 415)); }

bool is_mouse_in_third_button() { return (is_mouse_between_two_points(100, 480, 350, 730)); }

bool is_mouse_in_fourth_button() { return (is_mouse_between_two_points(445, 480, 695, 730 )); }



void handle_all_screnes_button_highlighting(menu_handler_data &global_menu_handler) 
{
    if (is_mouse_in_first_button()) 
        global_menu_handler.highlighted_button = FIRST;
    else if (is_mouse_in_second_button() && (global_menu_handler.game_state == HOME_SCREEN || global_menu_handler.game_state == SETTINGS_SCREEN )) 
        global_menu_handler.highlighted_button = SECOND;
    else if (is_mouse_in_third_button() && (global_menu_handler.game_state == HOME_SCREEN || global_menu_handler.game_state == SETTINGS_SCREEN )) 
        global_menu_handler.highlighted_button = THIRD;
    else if (is_mouse_in_fourth_button() && (global_menu_handler.game_state == HOME_SCREEN || global_menu_handler.game_state == SETTINGS_SCREEN ))
        global_menu_handler.highlighted_button = FOURTH;
    else
        global_menu_handler.highlighted_button = NONE;
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


void handle_settings_screen_actions(menu_handler_data &global_menu_handler) 
{

    handle_all_screnes_button_highlighting(global_menu_handler);

    if (is_mouse_in_first_button() && mouse_clicked(LEFT_BUTTON)) global_menu_handler.game_state = HOME_SCREEN;

    if (is_mouse_in_second_button() && mouse_clicked(LEFT_BUTTON)) (global_menu_handler.music_player.is_muted) ? global_menu_handler.music_player.is_muted = false : global_menu_handler.music_player.is_muted = true;

    if (is_mouse_in_third_button() && mouse_clicked(LEFT_BUTTON)) 
    {
        decrease_volume(global_menu_handler.music_player);
        global_menu_handler.music_player.changed_volume_required = true;
    }

    if (is_mouse_in_fourth_button() && mouse_clicked(LEFT_BUTTON)) 
    {
        increase_volume(global_menu_handler.music_player);
        global_menu_handler.music_player.changed_volume_required = true;
    }
}

void handle_home_screen_actions(menu_handler_data &global_menu_handler) 
{
    handle_all_screnes_button_highlighting(global_menu_handler);

    if (is_mouse_in_first_button() && mouse_clicked(LEFT_BUTTON)) global_menu_handler.game_state = PLAY_GAME_SCREEN;
    if (is_mouse_in_third_button() && mouse_clicked(LEFT_BUTTON)) global_menu_handler.game_state = SETTINGS_SCREEN;
}

void handle_menu_state(menu_handler_data &global_menu_handler) 
{
    switch (global_menu_handler.game_state) 
    {
        case HOME_SCREEN:
            draw_home_screen_background(global_menu_handler);
            handle_home_screen_actions(global_menu_handler);
            break;
        case SETTINGS_SCREEN:
            draw_settings_screen_background(global_menu_handler);
            handle_settings_screen_actions(global_menu_handler);
        default:
            break;
    }
    refresh_screen(60);
}






void handle_menu()
{
    menu_handler_data global_menu_handler = create_menu_handler();

    while ( ! quit_requested() )
    {
        clear_screen();
        if (global_menu_handler.game_state == PLAY_GAME_SCREEN) break;
        
        handle_music(global_menu_handler.music_player);
        handle_menu_state(global_menu_handler);

        process_events();
        
        refresh_screen();

    }

    if (global_menu_handler.game_state == PLAY_GAME_SCREEN) handle_game();
}



int main()
{
    open_window("Lost In Space", 800, 800);
    load_resources();

    load_menu_resources();

    
    handle_menu();

    return 0;
}
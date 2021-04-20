#include "./include/splashkit/splashkit.h"
#include "music_player.h"
#include "menu.h"
#include "lost_in_space.h"


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
    highlighted_button_state button = global_game_settings.highlighted_button;
    if (button != NONE) 
    {
        menu[button].erase(0,7);
        menu[button].insert(0, "highlighted");
    }
}

void draw_menu(const vector<string> menu) 
{
    draw_bitmap(menu.at(0), 0, 0);

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

            draw_bitmap(menu.at(button), x_location, y_location);
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


void draw_information_screen_background(const menu_handler_data &global_game_settings) 
{
    std::vector<string> information_screen_buttons 
    {
        "information_screen", "default_home_button", "default_clear_leaderboard_button"
    };

    append_vector_menu_buttons_to_highlight(global_game_settings, information_screen_buttons);

    draw_menu(information_screen_buttons);
}

void draw_leader_screen_background(const menu_handler_data &global_game_settings) 
{
    std::vector<string> information_screen_buttons 
    {
        "leaderboard_screen", "default_home_button", "default_repo_button"
    };

    append_vector_menu_buttons_to_highlight(global_game_settings, information_screen_buttons);

    draw_menu(information_screen_buttons);
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
    game_state current_state = global_menu_handler.game_state;

    //COMMENT HERE
    if (is_mouse_in_first_button()) 
        global_menu_handler.highlighted_button = FIRST;
    //COMMENT HERE
    else if (is_mouse_in_second_button()) 
        global_menu_handler.highlighted_button = SECOND;
    //COMMENT
    else if (is_mouse_in_third_button() && (current_state == HOME_SCREEN || current_state == SETTINGS_SCREEN )) 
        global_menu_handler.highlighted_button = THIRD;
    //COMMENT
    else if (is_mouse_in_fourth_button() && (current_state == HOME_SCREEN || current_state == SETTINGS_SCREEN ))
        global_menu_handler.highlighted_button = FOURTH;
    //COMMENT
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

    // COMMENT HERE
    if (is_mouse_in_first_button() && mouse_clicked(LEFT_BUTTON)) global_menu_handler.game_state = HOME_SCREEN;

     // COMMENT HERE
    if (is_mouse_in_second_button() && mouse_clicked(LEFT_BUTTON)) (global_menu_handler.music_player.is_muted) ? global_menu_handler.music_player.is_muted = false : global_menu_handler.music_player.is_muted = true;

     // COMMENT HERE
    if (is_mouse_in_third_button() && mouse_clicked(LEFT_BUTTON)) 
    {
        decrease_volume(global_menu_handler.music_player);
        global_menu_handler.music_player.changed_volume_required = true;
    }

     // COMMENT HERE
    if (is_mouse_in_fourth_button() && mouse_clicked(LEFT_BUTTON)) 
    {
        increase_volume(global_menu_handler.music_player);
        global_menu_handler.music_player.changed_volume_required = true;
    }
}

void handle_home_screen_actions(menu_handler_data &global_menu_handler) 
{
    handle_all_screnes_button_highlighting(global_menu_handler);

     // COMMENT HERE
    if (is_mouse_in_first_button() && mouse_clicked(LEFT_BUTTON)) global_menu_handler.game_state = PLAY_GAME_SCREEN;

     // COMMENT HERE
    if (is_mouse_in_second_button() && mouse_clicked(LEFT_BUTTON)) global_menu_handler.game_state = LEADERBOARD_SCREEN;

     // COMMENT HERE
    if (is_mouse_in_third_button() && mouse_clicked(LEFT_BUTTON)) global_menu_handler.game_state = SETTINGS_SCREEN;

    // COMMENT HERE
    if (is_mouse_in_fourth_button() && mouse_clicked(LEFT_BUTTON)) global_menu_handler.game_state = INFORMATION_SCREEN;
    
}

void handle_information_screen_actions(menu_handler_data &global_menu_handler)
{
    handle_all_screnes_button_highlighting(global_menu_handler);
     // COMMENT HERE
    if (is_mouse_in_first_button() && mouse_clicked(LEFT_BUTTON)) global_menu_handler.game_state = HOME_SCREEN;
    
}

void handle_leaderboard_screen_actions(menu_handler_data &global_menu_handler)
{
    handle_all_screnes_button_highlighting(global_menu_handler);
     // COMMENT HERE
    if (is_mouse_in_first_button() && mouse_clicked(LEFT_BUTTON)) global_menu_handler.game_state = HOME_SCREEN;
    
}

void handle_menu_state(menu_handler_data &global_menu_handler) 
{
    switch (global_menu_handler.game_state) 
    {
        case HOME_SCREEN:
            handle_home_screen_actions(global_menu_handler);
            draw_home_screen_background(global_menu_handler);
            break;
        case SETTINGS_SCREEN:
            handle_settings_screen_actions(global_menu_handler);
            draw_settings_screen_background(global_menu_handler);
            break;
        case INFORMATION_SCREEN:
            handle_information_screen_actions(global_menu_handler);
            draw_information_screen_background(global_menu_handler);
            break;
        case LEADERBOARD_SCREEN:
            handle_leaderboard_screen_actions(global_menu_handler);
            draw_leader_screen_background(global_menu_handler);
            break;
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

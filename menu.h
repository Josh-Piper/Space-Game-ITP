#ifndef MAIN_MENU
#define MAIN_MENU

#include "./include/splashkit/splashkit.h"
#include "music_player.h"
#include "lost_in_space.h"
#include <vector>


// TO DO -> UTILS

enum game_state { HOME_SCREEN, PLAY_GAME_SCREEN, LEADERBOARD_SCREEN, SETTINGS_SCREEN, INFORMATION_SCREEN };
enum highlighted_button_state { NONE, FIRST, SECOND, THIRD, FOURTH };

struct menu_handler_data
{
    game_state                      game_state;
    highlighted_button_state        highlighted_button;
    music_handler_data              music_player;
};

menu_handler_data create_menu_handler();
void append_vector_menu_buttons_to_highlight(const menu_handler_data &global_game_settings, std::vector<string> &menu);
void draw_menu(const vector<string> menu);
void draw_home_screen_background(const menu_handler_data &global_game_settings);
void draw_information_screen_background(const menu_handler_data &global_game_settings);
void draw_leader_screen_background(const menu_handler_data &global_game_settings);
void handle_game();
bool is_mouse_between_two_points(int first_x, int first_y, int second_x, int second_y);
bool is_mouse_in_first_button();
bool is_mouse_in_second_button();
bool is_mouse_in_third_button();
bool is_mouse_in_fourth_button();
void handle_all_screnes_button_highlighting(menu_handler_data &global_menu_handler);
void draw_settings_screen_background(menu_handler_data &global_menu_handler);
void handle_settings_screen_actions(menu_handler_data &global_menu_handler);
void handle_home_screen_actions(menu_handler_data &global_menu_handler);
void handle_information_screen_actions(menu_handler_data &global_menu_handler);
void handle_leaderboard_screen_actions(menu_handler_data &global_menu_handler);
void handle_menu_state(menu_handler_data &global_menu_handler);
void handle_menu();

#endif
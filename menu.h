#ifndef MAIN_MENU
#define MAIN_MENU

#include "./include/splashkit/splashkit.h"
#include "music_player.h"
#include <vector>

enum operating_system { WINDOWS, APPLE, LINUX, UNIX, UNIDENTIFIED };
enum game_state { END_GAME, HOME_SCREEN, PLAY_GAME_SCREEN, LEADERBOARD_SCREEN, SETTINGS_SCREEN, INFORMATION_SCREEN };
enum highlighted_button_state { NONE, FIRST, SECOND, THIRD, FOURTH };

struct menu_handler_data
{
    game_state                      game_state;
    highlighted_button_state        highlighted_button;
    music_handler_data              music_player;
};

#include "lost_in_space.h"


/**
 * Create a new home menu, thus, the game itself.
 * Used to handle any in-game changes such as music changes etc.
 * Will create and start playing the music for the game
 */ 
menu_handler_data create_menu_handler();

/**
 * Handle the highlighting of in-game buttons
 * 
 * @param                           global_game_settings    to check the button that the mouse is currently hovering over
 * @param                           menu                    the menu that needs to be appended dependent on the hovered button
 */ 
void append_vector_menu_buttons_to_highlight(const menu_handler_data &global_game_settings, std::vector<string> &menu);

/**
 * Draw the current screen dependent on the menu parameter
 * Menu holds the background and any buttons associated with it (only capable of handling 4 buttons)
 * 
 * @param                           menu
 */ 
void draw_menu(const vector<string> menu);

/**
 * Draw the home screen
 * @param                          global_game_settings     Passed to handle highlighting of buttons
 * 
 */ 
void draw_home_screen_background(const menu_handler_data &global_game_settings);

/**
 * Read in the information.text
 * Return the text that for that file
 * 
 */ 
vector<string> read_information_text();

/**
 * Write the text in a file to screen
 * after the two buttons, meant to be used in the menus
 * 
 * @param                          reading_file            the file that is being written to screen
 */ 
void draw_text_after_two_buttons(vector<string> reading_file);

/**
 * Draw the information screen
 * @param                          global_game_settings     Passed to handle highlighting of buttons
 * 
 */ 
void draw_information_screen_background(const menu_handler_data &global_game_settings);

/**
 * Draw the leaderboard screen
 * @param                          global_game_settings     Passed to handle highlighting of buttons
 * 
 */ 
void draw_leader_screen_background(const menu_handler_data &global_game_settings);

/**
 * Check if the mouse position is between two points. Note the parameters
 * 
 * @param                          first_x
 * @param                          first_y
 * @param                          second_x
 * @param                          second_y
 * 
 */ 
bool is_mouse_between_two_points(int first_x, int first_y, int second_x, int second_y);

/**
 * Check if the mouse is between the first button
 * Uses preset cords as all buttons are located in the same spot 
 */ 
bool is_mouse_in_first_button();

/**
 * Check if the mouse is between the second button
 * Uses preset cords as all buttons are located in the same spot 
 */ 
bool is_mouse_in_second_button();

/**
 * Check if the mouse is between the third button
 * Uses preset cords as all buttons are located in the same spot 
 */ 
bool is_mouse_in_third_button();

/**
 * Check if the mouse is between the fourth button
 * Uses preset cords as all buttons are located in the same spot 
 */ 
bool is_mouse_in_fourth_button();

/**
 * Changes the highlighted button stored in global_menu_handler depending where the mouse position is located
 * @param                          global_menu_handler
 * 
 */ 
void handle_all_screnes_button_highlighting(menu_handler_data &global_menu_handler);

/**
 * Draw the settings screen
 * @param                          global_menu_handler
 * 
 */ 
void draw_settings_screen_background(menu_handler_data &global_menu_handler);

/**
 * Handle any button presses from the setting screen
 * Handles any music related settings etc.
 * @param                          global_menu_handler
 * 
 */ 
void handle_settings_screen_actions(menu_handler_data &global_menu_handler);

/**
 * Handle any button presses from the home screen 
 * Allows the user to play the game and to navigate to other screens
 * @param                          global_menu_handler
 * 
 */ 
void handle_home_screen_actions(menu_handler_data &global_menu_handler);

/**
 * Handle any button presses from the information screen
 * @param                          global_menu_handler
 * 
 */ 
void handle_information_screen_actions(menu_handler_data &global_menu_handler);

/**
 * Handle any button presses from the leaderboard screen
 * @param                          global_menu_handler
 * 
 */ 
void handle_leaderboard_screen_actions(menu_handler_data &global_menu_handler);

/**
 * Update the game depending on the game_state stored in global_menu_handler
 * Allows the game to change and handle the necessary screens
 * @param                          global_menu_handler
 * 
 */ 
void handle_menu_state(menu_handler_data &global_menu_handler);

/**
 * Draw the paused screen
 * @param                          global_game_settings     Passed to handle highlighting of buttons
 * 
 */ 
void draw_settings_paused_screen_background(menu_handler_data &global_menu_handler);

/**
 * Handle the play-game paused menu
 * 
 */ 
bool paused_screen_menu(menu_handler_data &global_menu_handler);

/**
 * Handle the menu itself
 * Note it does not handle the game
 */ 
void handle_menu();



#endif
#ifndef MAIN_MENU
#define MAIN_MENU

#include "splashkit.h"
#include "../../Source/Utilities/music_player.h"
#include "../../Source/Utilities/leaderboard.h"
#include <vector>

enum operating_system { WINDOWS, APPLE, LINUX, UNIX, UNIDENTIFIED };
enum game_state { END_GAME, HOME_SCREEN, PLAY_GAME_SCREEN, LEADERBOARD_SCREEN, SETTINGS_SCREEN, INFORMATION_SCREEN }; // the different states of the game
enum highlighted_button_state { NONE, FIRST, SECOND, THIRD, FOURTH };

/**
 * The menu data
 * @param                          game_state               The current state of the application
 * @param                          highlighted_button       Which button is currently highlighted within the menus
 * @param                          music_player             The music player to keep playing music throughout the game
 * @param                          sort_type                Used for sorting data for the leaderboard. Can be extended to other parts of the application
 */ 
struct menu_handler_data
{
    game_state                      game_state;
    highlighted_button_state        highlighted_button;
    music_handler_data              music_player;
    sort_type                       sorting_method;
};

#include "../../Source/GameData/lost_in_space.h" // to allow the program to compile correctly

/**
 * Create a new home menu, thus, the game itself.
 * Used to handle any in-game changes such as music changes etc.
 * Will create and start playing the music for the game
 */ 
menu_handler_data create_menu_handler();

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
 */ 
void handle_all_screnes_button_highlighting(menu_handler_data &global_menu_handler);


/**
 * Handle any button presses from the setting screen
 * Handles any music related settings etc.
 * @param                          global_menu_handler
 */ 
void handle_settings_screen_actions(menu_handler_data &global_menu_handler);

/**
 * Handle any button presses from the home screen 
 * Allows the user to play the game and to navigate to other screens
 * @param                          global_menu_handler
 */ 
void handle_home_screen_actions(menu_handler_data &global_menu_handler);

/**
 * Handle any button presses from the information screen
 * @param                          global_menu_handler
 */ 
void handle_information_screen_actions(menu_handler_data &global_menu_handler);

/**
 * Handle any button presses from the leaderboard screen
 * @param                          global_menu_handler
 */ 
void handle_leaderboard_screen_actions(menu_handler_data &global_menu_handler);

/**
 * Update the game depending on the game_state stored in global_menu_handler
 * Allows the game to change and handle the necessary screens
 * @param                          global_menu_handler
 */ 
void handle_menu_state(menu_handler_data &global_menu_handler);

/**
 * Handle the play-game paused menu
 * Read the users actions within the pause screen,
 * thus allow the user to quit or resume the game
 * @param                          global_menu_handler
 * @param                          game
 */ 
bool handle_paused_screen_menu(menu_handler_data &global_menu_handler, game_data &game);

/**
 * Handle the end game sequence
 * Allow the user to save their score of the current play through
 * @param                          global_menu_handler      used to end the game or move to a particular menu after the ending
 * @param                          game                     used for the players current score
 */ 
bool handle_end_game_menu(menu_handler_data &global_menu_handler, game_data &game);

/**
 * Handle the menu itself
 * Note it does not handle the game
 */ 
void handle_menu();



#endif
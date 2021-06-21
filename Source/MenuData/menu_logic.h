#ifndef MAIN_MENU
#define MAIN_MENU

#include "splashkit.h"
#include "../../Source/Utilities/music_player.h"
#include "../../Source/Utilities/leaderboard.h"
#include <vector>

enum operating_system { WINDOWS, APPLE, LINUX, UNIX, UNIDENTIFIED };

enum game_state { END_GAME, HOME_SCREEN, PLAY_GAME_SCREEN, LEADERBOARD_SCREEN, 
    SETTINGS_SCREEN, INFORMATION_SCREEN }; 

enum highlighted_button_state { NONE, FIRST_BTN, SECOND_BTN, THIRD_BTN, FOURTH_BTN };

/**
 * The menu data
 * @field                                          game_state
 * @field                                          highlighted_button
 * @field                                          music_player
 * @field                                          leaderboard_sorting_method
 */ 
struct menu_handler_data
{
    game_state                      game_state;
    highlighted_button_state        highlighted_button;
    music_handler_data              music_player;
    sort_type                       leaderboard_sorting_method;
};

#include "../../Source/GameData/lost_in_space.h" 

/**
 * Create a new home menu, thus, the game itself.
 * Used to handle any in-game changes such as music changes etc.
 * Will create and start playing the music for the game
 */ 
menu_handler_data create_menu_handler();

/**
 * Changes the highlighted button stored in global_menu_handler 
 * depending where the mouse position is located
 * @param                                          global_menu_handler
 */ 
void handle_all_screens_button_hover_over_highlighting(
    menu_handler_data &global_menu_handler);


/**
 * Handle any button presses from the setting screen
 * Handles any music related settings etc.
 * @param                                          global_menu_handler
 */ 
void handle_settings_screen_actions(menu_handler_data &global_menu_handler);

/**
 * Handle any button presses from the home screen 
 * Allows the user to play the game and to navigate to other screens
 * @param                                          global_menu_handler
 */ 
void handle_home_screen_actions(menu_handler_data &global_menu_handler);

/**
 * Handle any button presses from the information screen
 * @param                                          global_menu_handler
 */ 
void handle_information_screen_actions(menu_handler_data &global_menu_handler);

/**
 * Handle any button presses from the leaderboard screen
 * @param                                          global_menu_handler
 */ 
void handle_leaderboard_screen_actions(menu_handler_data &global_menu_handler);

/**
 * Update the game depending on the game_state stored in global_menu_handler
 * Allows the game to change and handle the necessary screens
 * @param                                          global_menu_handler
 */ 
void handle_menu_state(menu_handler_data &global_menu_handler);

/**
 * Handle the play-game paused menu
 * Read the users actions within the pause screen,
 * thus allow the user to quit or resume the game
 * @param                                          global_menu_handler
 * @param                                          game
 */ 
bool handle_paused_screen_menu(menu_handler_data &global_menu_handler, 
    game_data &game);

/**
 * Handle adding a leaderboard entry via. text input
 * @param                                          global_menu_handler
 * @param                                          game
 * @param                                          has_entered_entry 
 */ 
void check_end_game_add_leaderboard_entry(
    menu_handler_data &global_menu_handler, game_data &game, 
    bool &has_entered_entry);

/**
 * Handle the end game sequence
 * Allow the user to save their score of the current play through
 * @param                                          global_menu_handler
 * @param                                          game
 */ 
bool handle_end_game_menu(
    menu_handler_data &global_menu_handler, game_data &game);

/**
 * Handle the menu itself
 * Note it does not handle the game
 */ 
void handle_menu();



#endif
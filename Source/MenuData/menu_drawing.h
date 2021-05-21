#ifndef MAIN_MENU_DRAWING
#define MAIN_MENU_DRAWING
#include "splashkit.h"
#include "menu_logic.h"
#include <vector>

/**
 * Handle the highlighting of in-game buttons
 * @param                                          global_game_settings    to check the button that the mouse is currently hovering over
 * @param                                          menu                    the menu that needs to be appended dependent on the hovered button
 */ 
void append_vector_menu_buttons_to_highlight(const menu_handler_data &global_game_settings, std::vector<string> &menu);

/**
 * Draw the current screen dependent on the menu parameter
 * Menu holds the background and any buttons associated with it (only capable of handling 4 buttons)
 * 
 * @param                                          menu
 */ 
void draw_menu(const vector<string> menu);

/**
 * Write the text in a file to screen
 * after the two buttons, meant to be used in the menus
 * 
 * @param                                          reading_file            the file that is being written to screen
 */ 
void draw_text_after_two_buttons(vector<string> reading_file);

/**
 * Draw the home screen
 * @param                                          global_game_settings     Passed to handle highlighting of buttons
 * 
 */ 
void draw_home_screen_background(const menu_handler_data &global_game_settings);

/**
 * Draw the information screen
 * @param                                          global_game_settings     Passed to handle highlighting of buttons
 * 
 */ 
void draw_information_screen_background(const menu_handler_data &global_game_settings);

/**
 * Draw leaderboard sorting button depending on the sorting method
 * @param                                          sorting_method
 */ 
void draw_leaderboard_sorting_button(sort_type sorting_method);

/**
 * Draw the leaderboard screen
 *@param                                           global_game_settings
 */ 
void draw_leaderboard_screen_background(const menu_handler_data &global_game_settings);

/**
 * Draw the settings screen
 * @param                                          global_menu_handler
 * 
 */ 
void draw_settings_screen_background(menu_handler_data &global_menu_handler);

/**
 * Draw the paused screen
 * @param                                          global_game_settings     Passed to handle highlighting of buttons
 * 
 */ 
void draw_settings_paused_screen_background(menu_handler_data &global_menu_handler);

/**
 * Form the paused menu information
 * @param                                          game                     Passed to create a vector<string> as the paused menu information
 */ 
vector<string> form_paused_menu_information(game_data &game);

/**
 * Insert the default end game messages
 * @param                                          vec
 */ 
void insert_end_game_messages(vector<string> &vec);

/**
 * Insert the end message dependent on players level
 * @param                                          level
 */ 
string get_end_message_from_level(int level);

/**
 * Draw the end game screen with the users score of the current playthrough
 * @param                                          global_menu_handler
 * @param                                          score                     players current score
 * @param                                          level
 */ 
void draw_end_game_screen_background(menu_handler_data &global_menu_handler, int score, int level);

#endif
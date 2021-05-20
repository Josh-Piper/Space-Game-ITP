#ifndef MENU_UTILITIES
#define MENU_UTILITIES

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
 * Check if mouse clicked first button
 */ 
bool has_mouse_clicked_first_button();

/**
 * Check if mouse clicked second button
 */ 
bool has_mouse_clicked_second_button();

/**
 * Check if mouse clicked third button
 */ 
bool has_mouse_clicked_third_button();

/**
 * Check if mouse clicked fourth button
 */ 
bool has_mouse_clicked_fourth_button();

/**
 * Check if mouse held first button
 */ 
bool has_mouse_held_first_button();

/**
 * Check if mouse held second button
 */ 
bool has_mouse_held_second_button();

/**
 * Check if mouse held third button
 */ 
bool has_mouse_held_third_button();

/**
 * Check if mouse held fourth button
 */ 
bool has_mouse_held_fourth_button();

#endif
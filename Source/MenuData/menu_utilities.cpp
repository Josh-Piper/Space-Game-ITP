#include "splashkit.h"

bool is_mouse_between_two_points(int first_x, int first_y, int second_x, int second_y) { return ((mouse_x() >= first_x && mouse_x() <= second_x) && (mouse_y() >= first_y && mouse_y() <= second_y)); }

bool is_mouse_in_first_button() { return (is_mouse_between_two_points(100, 165, 350, 415)); }

bool is_mouse_in_second_button() { return (is_mouse_between_two_points(445, 165, 695, 415)); }

bool is_mouse_in_third_button() { return (is_mouse_between_two_points(100, 480, 350, 730)); }

bool is_mouse_in_fourth_button() { return (is_mouse_between_two_points(445, 480, 695, 730 )); }

bool has_mouse_clicked_first_button() { return (is_mouse_in_first_button() && mouse_clicked(LEFT_BUTTON)); }

bool has_mouse_clicked_second_button() { return (is_mouse_in_second_button() && mouse_clicked(LEFT_BUTTON)); }

bool has_mouse_clicked_third_button() { return (is_mouse_in_third_button() && mouse_clicked(LEFT_BUTTON)); }

bool has_mouse_clicked_fourth_button() { return (is_mouse_in_fourth_button() && mouse_clicked(LEFT_BUTTON)); }

bool has_mouse_held_first_button() { return (is_mouse_in_first_button() && mouse_down(LEFT_BUTTON)); }

bool has_mouse_held_second_button() { return (is_mouse_in_second_button() && mouse_down(LEFT_BUTTON)); }

bool has_mouse_held_third_button() { return (is_mouse_in_third_button() && mouse_down(LEFT_BUTTON)); }

bool has_mouse_held_fourth_button() { return (is_mouse_in_fourth_button() && mouse_down(LEFT_BUTTON)); }
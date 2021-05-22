#include "splashkit.h"
#include "algorithm"
#include <vector>
#include <algorithm>

bool is_mouse_between_two_points(int first_x, int first_y, int second_x, int second_y) 
{ 
    return ((mouse_x() >= first_x && mouse_x() <= second_x) && (mouse_y() >= first_y && mouse_y() <= second_y)); 
}

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

bool has_mouse_clicked_leaderboard_button() { return (is_mouse_between_two_points(560, 750, 790, 800) && mouse_clicked(LEFT_BUTTON)); }

int index_of_longest_string_in_strings(vector<string> strings)
{
    auto longest_string_in_strings = std::max_element(strings.begin(), strings.end(), 
    [] (const string &a, const string &b) 
    { 
        return a.length() < b.length(); 
    });

    int index_of_longest_string = std::distance(strings.begin(), longest_string_in_strings);

    return index_of_longest_string;
}

int font_size_depending_on_files_info(vector<string> file_to_read)
{
    int font_size = INT_MAX;

    int index_of_longest_string_in_file = index_of_longest_string_in_strings(file_to_read);
    int font_size_depending_on_longest_string = 1800 / file_to_read.at(index_of_longest_string_in_file).length(); 

    // Set the font size dependent on the amount of rows of text or longest length of a singular row
    if (file_to_read.size() > 5) font_size = 50;
    if (font_size_depending_on_longest_string < font_size) font_size = font_size_depending_on_longest_string;

    return font_size;
}

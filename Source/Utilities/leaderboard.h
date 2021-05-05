#ifndef LEADERBOARD
#define LEADERBOARD
#include "splashkit.h"
#include <vector>

/**
 * Leaderboard object
 */  
struct leaderboard_entry_data
{
    string message;                 // format name          -> score
    string time_uploaded;           //format mm/dd/yy hh:mm:ss
};

// Sorting Types
enum sort_type {
    ALPHA_ASCENDING,
    ALPHA_DESCENDING,
    DATE_ASCENDING,
    DATE_DESCENDING
};

/**
 * Read the current time and date of the locale system
 * Formatted in mm/dd/yy hh:mm::ss
 * Used for sorting purposes
 */ 
string get_current_time();

/**
 * Read in the information.text
 * Return the text that for that file
 * 
 */ 
vector<string> read_information_text();

/**
 * Reset the leaderboard file
 */ 
void reset_leaderboard_file();

/**
 * Add a new entry to the leaderboard file
 * @param                          name                     The name of the person
 * @param                          score                    The score the user achieved 
 */ 
void add_new_leaderboard_entry(string name, int score);

/**
 * Read the leaderboard information
 * Create a new leaderboard if non-existent
 * Then return the lines within the file as a vector<string>
 */ 
vector<string> read_leaderboard_text();

vector<leaderboard_entry_data> create_leaderboard_vector_from_file();

bool sort_leaderboard_alphabetically_ascending(const leaderboard_entry_data &lhs, const leaderboard_entry_data &rhs);

bool sort_leaderboard_alphabetically_descending(const leaderboard_entry_data &lhs, const leaderboard_entry_data &rhs);

bool sort_leaderboard_date_ascending(const leaderboard_entry_data &lhs, const leaderboard_entry_data &rhs);

bool sort_leaderboard_date_descending(const leaderboard_entry_data &lhs, const leaderboard_entry_data &rhs);

void return_leaderboard_sorted(vector<leaderboard_entry_data> &my_vec, sort_type sorting_method);

vector<string> convert_leaderboard_entry_vector_to_string_vector(const vector<leaderboard_entry_data> &my_vec);

sort_type change_type(sort_type current);

#endif
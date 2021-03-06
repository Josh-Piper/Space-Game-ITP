#ifndef LEADERBOARD
#define LEADERBOARD
#include "splashkit.h"
#include <vector>

/**
 * Leaderboard object
 * format mm/dd/yy hh:mm:ss
 * @field                                          message
 * @field                                          time_uploaded
 * @field                                          score
 */  
struct leaderboard_entry_data
{
    string                          message;
    string                          time_uploaded;
    long long                       score;
};

// Sorting Types
enum sort_type {
    ALPHA_ASCENDING,
    ALPHA_DESCENDING,
    DATE_ASCENDING,
    DATE_DESCENDING,
    SCORE_ASCENDING,
    SCORE_DESCENDING
};

/**
 * Read the current time and date of the locale system
 * Formatted in mm/dd/yy hh:mm::ss
 * Used for sorting purposes
 */ 
string get_current_time();

/**
 * Return the default information file information
 */ 
vector<string> get_default_information_data();

/**
 * Reset the information file
 */ 
void reset_information_file();

/**
 * Read in the information.text
 * Return the text that for that file
 * 
 */ 
vector<string> read_information_file();

/**
 * Reset the leaderboard file
 */ 
void reset_leaderboard_file();

/**
 * Add a new entry to the leaderboard file
 * @param                                          name
 * @param                                          score
 */ 
void add_new_leaderboard_entry(string name, int score);

/**
 * Return if the leaderboard file is valid
 * @param                                          leaderboard
 */ 
bool is_leaderboard_file_valid(vector<string> leaderboard);

/**
 * Read the leaderboard information
 * Create a new leaderboard if non-existent
 * Then return the lines within the file as a vector<string>
 */ 
vector<string> read_leaderboard_text();

/**
 * Create a vector of leaderboard_entry_data objects from the leaderboard file
 * Splits the file by its delimeters to get the objects values for:
 * message
 * date it was created
 * score
 */ 
vector<leaderboard_entry_data> create_leaderboard_vector_from_file();

/**
 * Sort the leaderboard vector alphabetically ascending
 * @param                                          lhs
 * @param                                          rhs
 */
bool sort_leaderboard_alphabetically_ascending(
    const leaderboard_entry_data &lhs, const leaderboard_entry_data &rhs);

/**
 * Sort the leaderboard vector alphabetically descending
 * @param                                          lhs
 * @param                                          rhs
 */
bool sort_leaderboard_alphabetically_descending(
    const leaderboard_entry_data &lhs, const leaderboard_entry_data &rhs);

/**
 * Sort the leaderboard vector date ascending
 * @param                                          lhs
 * @param                                          rhs
 */
bool sort_leaderboard_date_ascending(
    const leaderboard_entry_data &lhs, const leaderboard_entry_data &rhs);

/**
 * Sort the leaderboard vector date descending
 * @param                                          lhs
 * @param                                          rhs                            
 */
bool sort_leaderboard_date_descending(
    const leaderboard_entry_data &lhs, const leaderboard_entry_data &rhs);

/**
 * Sort the leaderboard vector score ascending
 * @param                                          lhs
 * @param                                          rhs
 */
bool sort_leaderboard_score_ascending(
    const leaderboard_entry_data &lhs, const leaderboard_entry_data &rhs);

/**
 * Sort the leaderboard vector alphabetically descending
 * @param                                          score
 * @param                                          rhs
 */
bool sort_leaderboard_score_descending(
    const leaderboard_entry_data &lhs, const leaderboard_entry_data &rhs);

/**
 * General procedure to convert a vector of leaderboard_entry_data into its 
 * sorted form. The value sorting options are dependent on the 
 * sorting_method parsed in.
 * @param                                          my_vec
 * @param                                          sorting_method
 */
void return_leaderboard_sorted(
    vector<leaderboard_entry_data> &my_vec, sort_type sorting_method);

/**
 * Convert the leaderboard vector into its messages, thus, 
 * removing the score and date inputted data
 * @param                                          my_vec
 */
vector<string> convert_leaderboard_entry_vector_to_string_vector(
    const vector<leaderboard_entry_data> &my_vec);

/**
 * Change the type of the sorting
 * @param                                          current
 */
void change_sorting_type(sort_type &current);

#endif
#ifndef LEADERBOARD
#define LEADERBOARD
#include "splashkit.h"
#include <vector>

/**
 * Read in the information.text
 * Return the text that for that file
 * 
 */ 
vector<string> read_information_text();

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

/**
 * Reset the leaderboard file
 */ 
void reset_leaderboard_file();

/**
 * Draw the leaderboard screen
 * @param                          global_game_settings     Passed to handle highlighting of buttons
 * 
 */ 

#endif
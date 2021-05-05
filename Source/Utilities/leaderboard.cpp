#include "splashkit.h"
#include <vector>
#include "leaderboard.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <map>
#include <iterator>
#include <algorithm>

using std::to_string;
using std::endl;
using std::ofstream;
using std::ifstream;

static const string INFORMATION_FILE_LOCATION = "./Source/Utilities/information.txt";
static const string LEADERBOARD_FILE_LOCATION = "./Source/Utilities/leaderboard.txt";
static const string LEADERBOARD_DEFAULT_MESSAGE = "Leader Board";

string get_current_time()
{
  
    //Get the date and time
    time_t _current_time = time(0);
    char current_time [100];
    // Convert the date to be comparable for the leaderboard.
    strftime(current_time, sizeof(current_time), "%c", std::localtime(&_current_time)); //%d %x
    return current_time;
}

vector<string> read_information_text()
{
    string line;
    vector<string> result;
    ifstream info_text_file { INFORMATION_FILE_LOCATION };

    // Read from the file if it exists
    if (info_text_file.is_open())
    {
        while ( getline (info_text_file, line) )
        result.push_back(line);
    }   
    // Create a new file to read from if one does not exist
    else if (info_text_file.fail())
    {
        ofstream new_file( INFORMATION_FILE_LOCATION );
        new_file << "Lost in Space";
        new_file << "More Information Will Be Added Soon!";
        new_file.close();
    }
    info_text_file.close();
    return result;
}   

void reset_leaderboard_file()
{
    ofstream new_file( LEADERBOARD_FILE_LOCATION );
    new_file << LEADERBOARD_DEFAULT_MESSAGE;
    new_file.close();
}

void add_new_leaderboard_entry(string name, int score)
{
    string current_time = get_current_time();
    string entry = name + "                  -> Current Score: " + to_string(score) + ">>" + get_current_time();
    ofstream leaderboard_file;

    // Append to leaderboard file
    leaderboard_file.open(LEADERBOARD_FILE_LOCATION, std::ios_base::app);

    // If the user tries to add to a leaderboard file that doesn't exist. Note this is
    // an edge case for when the user plays the game first, thus, no file was genned.
    if (leaderboard_file.fail()) reset_leaderboard_file();
    leaderboard_file << endl << entry;

    leaderboard_file.close();
}

vector<string> read_leaderboard_text()
{
    string line;
    vector<string> result;
    ifstream leaderboard_file { LEADERBOARD_FILE_LOCATION };

    if (leaderboard_file.is_open())
    {
        // Loop through each line in leaderboard file
        while ( getline (leaderboard_file, line) )
            result.push_back(line);   
    } 
    else
    {
        reset_leaderboard_file(); // if leaderboard does not exist. Create one
    }
    
    leaderboard_file.close();
    return result;
}

vector<leaderboard_entry_data> create_leaderboard_vector_from_file()
{
    vector<string> leaderboard_data = read_leaderboard_text();
    vector<leaderboard_entry_data> result;

    for (string complete_message: leaderboard_data)
    {
        // Append the message from the file. Note the delimeter >> seperates the message and date uploaded
        int delim_location = complete_message.find(">>");
        leaderboard_entry_data entry;
        entry.message = complete_message.substr(0, delim_location);
        entry.time_uploaded = complete_message.substr(delim_location + 2, complete_message.length() - 1);
        result.push_back(entry);
    }
    return result;
}

bool sort_leaderboard_alphabetically_ascending(const leaderboard_entry_data &lhs, const leaderboard_entry_data &rhs) { return lhs.message < rhs.message; }

bool sort_leaderboard_alphabetically_descending(const leaderboard_entry_data &lhs, const leaderboard_entry_data &rhs) { return lhs.message > rhs.message; }

bool sort_leaderboard_date_ascending(const leaderboard_entry_data &lhs, const leaderboard_entry_data &rhs) { return lhs.time_uploaded < rhs.time_uploaded; }

bool sort_leaderboard_date_descending(const leaderboard_entry_data &lhs, const leaderboard_entry_data &rhs) { return lhs.time_uploaded > rhs.time_uploaded; }

void return_leaderboard_sorted(vector<leaderboard_entry_data> &my_vec, sort_type sorting_method)
{
    switch (sorting_method)
    {
        case ALPHA_ASCENDING: sort(my_vec.begin(), my_vec.end(), sort_leaderboard_alphabetically_ascending); break;
        case ALPHA_DESCENDING: sort(my_vec.begin(), my_vec.end(), sort_leaderboard_alphabetically_descending); break;
        case DATE_ASCENDING: sort(my_vec.begin(), my_vec.end(), sort_leaderboard_date_ascending); break;
        case DATE_DESCENDING: sort(my_vec.begin(), my_vec.end(), sort_leaderboard_date_descending); break;
        default: break;
    }
}

vector<string> convert_leaderboard_entry_vector_to_string_vector(const vector<leaderboard_entry_data> &my_vec)
{
    vector<string> result;

    // Put the Leader Board message at the top of the file and then append the sorting data

    // Append the Leader Board message
    for (leaderboard_entry_data data: my_vec)
    {
        if (data.message == LEADERBOARD_DEFAULT_MESSAGE) result.push_back(data.message);
    }

    // Append the Data
    for (leaderboard_entry_data data: my_vec)
    {
        if (data.message == LEADERBOARD_DEFAULT_MESSAGE) continue;
        result.push_back(data.message);
    }

    return result;
}

sort_type change_type(sort_type current)
{
    sort_type result = ALPHA_ASCENDING;  

    switch (current)
    {
        case ALPHA_ASCENDING: result = ALPHA_DESCENDING; break;
        case ALPHA_DESCENDING: result = DATE_ASCENDING; break;
        case DATE_ASCENDING: result = DATE_DESCENDING; break;
        default: break;
    }
    return result;
}

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

// Global constant variables
static const string INFORMATION_FILE_LOCATION = 
    "./Source/Utilities/information.txt";
static const string LEADERBOARD_FILE_LOCATION = 
    "./Source/Utilities/leaderboard.txt";
static const string LEADERBOARD_DEFAULT_MESSAGE = "Leader Board";

string get_current_time()
{
    time_t today = time(0); 
    tm *time_today = std::localtime(&today);
    char today_formatted [100]; 
    
    strftime(today_formatted, sizeof(today_formatted), "%c", time_today); 
    return today_formatted;
}

vector<string> get_default_information_data()
{
    static const vector<string> INFORMATION_FILE_DATA =
    {
        "Lost in Space",
        "An action packed Space Adventure game!",
        "Note - you can only kill space fighters when you have a shield",
        "Level 1 - Survive for 60 Seconds",
        "Level 2 - Survive from Space Fighters for 60 Seconds",
        "Level 3 - Not Implemented Yet."
    };
    return INFORMATION_FILE_DATA;
}
void reset_information_file()
{
    ofstream new_file( INFORMATION_FILE_LOCATION );
    for (string info_message: get_default_information_data())
        new_file << info_message << endl;
    new_file.close();
}

vector<string> read_information_file() 
{
    string line;
    vector<string> result;
    ifstream info_text_file { INFORMATION_FILE_LOCATION };

    if (info_text_file.fail())
    {
        reset_information_file();
        return get_default_information_data();
    }

    if (info_text_file.is_open())
    {
        while ( getline (info_text_file, line) )
            result.push_back(line);
    }
           
    info_text_file.close();
    return result;
}   

void reset_leaderboard_file()
{
    ofstream new_file( LEADERBOARD_FILE_LOCATION );
    new_file.close();
}

void add_new_leaderboard_entry(string name, int score)
{
    string current_time = get_current_time();
    string entry = name + "                  -> Current Score: " + 
        to_string(score) + ">>" + get_current_time();
    ofstream leaderboard_file;

    leaderboard_file.open(LEADERBOARD_FILE_LOCATION, std::ios_base::app);

    // If the user tries to add to a leaderboard file that doesn't exist. 
    // This is an edge case for when the user plays the game first, 
    // thus, no file was genned.
    if (leaderboard_file.fail()) reset_leaderboard_file();
    leaderboard_file << entry << endl; 
    leaderboard_file.close();
}

bool is_leaderboard_file_valid(vector<string> leaderboard)
{
    for (string msg: leaderboard)
    {
        int time_delim_location = msg.find(">>");
        int score_delim_location = msg.find("Score: ") + 7;

        // File does not contain the delimeters
        if (time_delim_location == string::npos || 
            score_delim_location == string::npos)
        {
            return false;
        }
    }
    return true;
}

vector<string> read_leaderboard_text()
{
    string line;
    vector<string> result;
    ifstream leaderboard_file { LEADERBOARD_FILE_LOCATION };

    if (leaderboard_file.is_open())
    {
        while ( getline (leaderboard_file, line) )
            result.push_back(line);   
    } 
    else
    {
        reset_leaderboard_file(); 
    }
    
    leaderboard_file.close();

    if (! is_leaderboard_file_valid(result)) 
    {
        reset_leaderboard_file();
        return { }; 
    }

    return result;
}

vector<leaderboard_entry_data> create_leaderboard_vector_from_file()
{
    vector<string> leaderboard_data = read_leaderboard_text();
    vector<leaderboard_entry_data> result;

    for (string complete_message: leaderboard_data)
    {
        leaderboard_entry_data entry;
        int time_delim_location = complete_message.find(">>");
        int score_delim_location = complete_message.find("Score: ") + 7; 

        entry.message = complete_message.substr(0, time_delim_location);
        entry.time_uploaded = complete_message.substr(time_delim_location + 2, 
            complete_message.length() - 1); 
        
        try
        {
            entry.score = std::stoll ( complete_message.substr( 
                score_delim_location, time_delim_location - 1 ) );
        }
        catch (int exception) 
        {
             entry.score = 0;
        }

        result.push_back(entry);
    }
    return result;
}

bool sort_leaderboard_alphabetically_ascending(
    const leaderboard_entry_data &lhs, const leaderboard_entry_data &rhs) 
{ 
    return lhs.message > rhs.message; 
}

bool sort_leaderboard_alphabetically_descending(
    const leaderboard_entry_data &lhs, const leaderboard_entry_data &rhs) 
{ 
    return lhs.message < rhs.message; 
}

bool sort_leaderboard_date_ascending(
    const leaderboard_entry_data &lhs, const leaderboard_entry_data &rhs) 
{
    return lhs.time_uploaded < rhs.time_uploaded; 
}

bool sort_leaderboard_date_descending(
    const leaderboard_entry_data &lhs, const leaderboard_entry_data &rhs) 
{
    return lhs.time_uploaded > rhs.time_uploaded; 
}

bool sort_leaderboard_score_ascending(
    const leaderboard_entry_data &lhs, const leaderboard_entry_data &rhs) 
{ 
    return lhs.score > rhs.score; 
}

bool sort_leaderboard_score_descending(
    const leaderboard_entry_data &lhs, const leaderboard_entry_data &rhs)   
{ 
    return lhs.score < rhs.score; 
}

void return_leaderboard_sorted(
    vector<leaderboard_entry_data> &my_vec, sort_type sorting_method)
{
    switch (sorting_method)
    {
        case ALPHA_ASCENDING: 
            sort(my_vec.begin(), my_vec.end(), 
                sort_leaderboard_alphabetically_ascending); 
            break;
        case ALPHA_DESCENDING: 
            sort(my_vec.begin(), my_vec.end(), 
                sort_leaderboard_alphabetically_descending); 
            break;
        case DATE_ASCENDING: 
            sort(my_vec.begin(), my_vec.end(), 
                sort_leaderboard_date_ascending); 
            break;
        case DATE_DESCENDING: 
            sort(my_vec.begin(), my_vec.end(), 
                sort_leaderboard_date_descending); 
            break;
        case SCORE_ASCENDING: 
            sort(my_vec.begin(), my_vec.end(), 
                sort_leaderboard_score_ascending); 
            break;
        case SCORE_DESCENDING: 
            sort(my_vec.begin(), my_vec.end(), 
                sort_leaderboard_score_descending);
            break;
        default: 
            break;
    }
}

vector<string> convert_leaderboard_entry_vector_to_string_vector(
    const vector<leaderboard_entry_data> &my_vec)
{
    vector<string> result;

    result.push_back(LEADERBOARD_DEFAULT_MESSAGE);
    for (leaderboard_entry_data data: my_vec)
        result.push_back(data.message);

    return result;
}

void change_sorting_type(sort_type &current)
{
    sort_type new_sorting_method = ALPHA_ASCENDING;  

    switch (current)
    {
        case ALPHA_ASCENDING: new_sorting_method = ALPHA_DESCENDING; break;
        case ALPHA_DESCENDING: new_sorting_method = DATE_ASCENDING; break;
        case DATE_ASCENDING: new_sorting_method = DATE_DESCENDING; break;
        case DATE_DESCENDING: new_sorting_method = SCORE_ASCENDING; break;
        case SCORE_ASCENDING: new_sorting_method = SCORE_DESCENDING; break;
        default: break;
    }
    current = new_sorting_method;
}
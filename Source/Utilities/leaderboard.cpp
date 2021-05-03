#include "splashkit.h"
#include <vector>
#include <fstream>
#include <iostream>

using std::to_string;
using std::endl;
using std::ofstream;
using std::ifstream;

static const string INFORMATION_FILE_LOCATION = "./Source/Utilities/information.txt";
static const string LEADERBOARD_FILE_LOCATION = "./Source/Utilities/leaderboard.txt";

vector<string> read_information_text()
{
    string line;
    vector<string> result;

    ifstream info_text_file { INFORMATION_FILE_LOCATION };


    if (info_text_file.is_open())
    {
        while ( getline (info_text_file, line) )
        result.push_back(line);
    }   
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

void add_new_leaderboard_entry(string name, int score)
{
    string entry = name + "                  -> Current Score: " + to_string(score);

    ofstream leaderboard_file;
    leaderboard_file.open(LEADERBOARD_FILE_LOCATION, std::ios_base::app);

    leaderboard_file << endl << entry;
    leaderboard_file.close();
}

void reset_leaderboard_file()
{
    ofstream new_file( LEADERBOARD_FILE_LOCATION );
    new_file << "Leader Board";
    new_file.close();
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
    // if leaderboard does not exist. Create one
    else if ( leaderboard_file.fail() )
    {
        reset_leaderboard_file();
    }

    leaderboard_file.close();
    return result;
}

#include "splashkit.h"
#include <vector>
#include <fstream>
#include <iostream>

using std::to_string;
using std::endl;
using std::ofstream;
using std::ifstream;

vector<string> read_information_text()
{
    string line;
    vector<string> result;
    ifstream info_text_file {"information.txt"};
    if (info_text_file.is_open())
    {
        while ( getline (info_text_file, line) )
        result.push_back(line);
    }   
    info_text_file.close();
    return result;
}   

void add_new_leaderboard_entry(string name, int score)
{
    string entry = name + "                  -> Current Score: " + to_string(score);

    ofstream leaderboard_file;
    leaderboard_file.open("leaderboard.txt", std::ios_base::app);

    leaderboard_file << endl << entry;
    leaderboard_file.close();
}

void reset_leaderboard_file()
{
    ofstream new_file("leaderboard.txt");
    new_file << "Leader Board";
    new_file.close();
}

vector<string> read_leaderboard_text()
{
    string line;
    vector<string> result;
    ifstream leaderboard_file {"leaderboard.txt"};

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

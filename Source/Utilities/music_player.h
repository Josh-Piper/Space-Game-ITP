#ifndef MUSIC_PLAYER
#define MUSIC_PLAYER

#include "splashkit.h"

struct music_handler_data
{
    string          current_song;
    float           current_volume;
    bool            changed_volume_required;
    bool            is_muted;
};

bool is_increase_new_volume_valid(float volume);

bool is_decrease_new_volume_valid(float volume);

// Increase the volume of a given music_player if the next volume is valid
void increase_volume(music_handler_data &music_player);

// Decrease the volume of a given music_player if the next volume is valid
void decrease_volume(music_handler_data &music_player);

std::string get_current_volume_as_percentage(music_handler_data &music_player);

music_handler_data create_music_handler();

/**
 * Return the next song number
 * Acts as a limitter. I.e. if original_number is the final song, then return the first song number
 * @param original_number   The number of the song being currently played
 */ 
int get_next_song_number(string original_number);

/**
 * Return the full string name of the next song
 * Utilises get_next_song_number to attach the new name
 * @param original_number   The number of the song being currently played
 */ 
string return_next_song(string current_song);

/**
 * The music played in-game will react to the settings accordingly.
 * For example, will do the required SplashKit commands when the music_handler is muted.
 * @param music_handler     The music handler
 * 
 */ 
void handle_music(music_handler_data &music_handler);

#endif
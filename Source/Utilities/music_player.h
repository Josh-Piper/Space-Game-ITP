#ifndef MUSIC_PLAYER
#define MUSIC_PLAYER

#include "splashkit.h"

/**
 * Music handler data object
 * @field                                          current_song
 * @field                                          current_volume
 * @field                                          changed_volume_required
 * @field                                          is_muted
 */ 
struct music_handler_data
{
    string          current_song;       
    float           current_volume;
    bool            changed_volume_required;
    bool            is_muted;
};

/**
 * Is the new increased volume valid
 * @param                                          volume
 */ 
bool is_music_new_increase_volume_valid(float volume);

/**
 * Is the new decreased volume valid
 * @param                                          volume
 */ 
bool is_music_new_decrease_volume_valid(float volume);

/**
 * Handling music pausing and unpausing
 * @param                                          music_player
 */ 
void handle_music_pausing(music_handler_data &music_player);

/**
 * Increase music volume
 * @param                                          music_player
 */ 
void increase_music_volume(music_handler_data &music_player);

/**
 * Decrease music volume
 * @param                                          music_player
 */ 
void decrease_music_volume(music_handler_data &music_player);

/**
 * Get the volume as a percentage to use it as a string value. 
 * @param                                          music_player
 */ 
std::string get_current_volume_as_percentage(music_handler_data &music_player);

/**
 * Create the music handler with default values
 * Will initialise to 50% volume and no song
 */ 
music_handler_data create_music_handler();

/**
 * Return the next song number
 * Acts as a limitter. I.e. if original_number is the final song, 
 * then return the first song number
 * @param                                          original_number
 */ 
int get_next_song_number(string original_number);

/**
 * Return the full string name of the next song
 * Utilises get_next_song_number to attach the new name
 * @param                                          original_number
 */ 
string return_next_song(string current_song);

/**
 * The music played in-game will react to the settings accordingly.
 * For example, will do the required SplashKit commands when the music_handler
 * is muted.
 * @param                                          music_handler
 * 
 */ 
void handle_music(music_handler_data &music_handler);

#endif
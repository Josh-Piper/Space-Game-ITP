#include "music_player.h"
#include "splashkit.h"

bool is_increase_new_volume_valid(float volume) { return ((volume += 0.1) <= 1.1); }; //restrict volume between 0.0 and 1.0

bool is_decrease_new_volume_valid(float volume) { return ((volume -= 0.1) >= 0.0); } //restrict volume between 0.0 and 1.0

// increase the volume of a music_player when the new volume is valid
void increase_volume(music_handler_data &music_player) { if (is_increase_new_volume_valid(music_player.current_volume)) music_player.current_volume += 0.1; }

// decrease the volume of a music_player when the new volume is valid
void decrease_volume(music_handler_data &music_player) { if (is_decrease_new_volume_valid(music_player.current_volume)) music_player.current_volume -= 0.1; }

std::string get_current_volume_as_percentage(music_handler_data &music_player) 
{
    string str { std::to_string(music_player.current_volume).substr(0, 3) }; // get the volume in decimal form (only need the first 3, i.e. 0.35)
    if (str == "1.0") return "100%";
    if (str == "0.0") return "0%";
    return str.substr(2, 1).append("0%"); // return the percentage as the last 2 decimals, i.e. 0.35 -> 35%
}

music_handler_data create_music_handler()
{
    music_handler_data result;
    result.current_song = "music4"; // initialise to no song and let handle_music deal with which song is played
    result.current_volume = 0.0f; //Change back to play the current music
    result.changed_volume_required = false;
    result.is_muted = false;
    return result;
}

int get_next_song_number(string original_number) 
{
    static const int MAX_SONGS = 5;
    int song_number { std::stoi(original_number) }, return_number;    

    // If the next song number is greater than the max song number, then return the first song number
    (song_number + 1 < MAX_SONGS) ? return_number = song_number + 1 : return_number = 1;
    return return_number;
}


string return_next_song(string current_song) 
{
    string current_number {current_song.substr(current_song.length() - 1, 1)};
    string new_number {std::to_string(get_next_song_number(current_number))};
    return current_song.substr(0, current_song.length() - 1).append(new_number);
}

void handle_music(music_handler_data &music_handler) 
{   
    // once a song finishes, transition to play the next song
    
    if ( ! music_playing() ) 
    {
        music_handler.current_song = return_next_song(music_handler.current_song);
        fade_music_in(music_handler.current_song, 3000);
        set_music_volume(music_handler.current_volume);
    }

    // change the volume of the music player when the volume is changed in-game
    if (music_handler.changed_volume_required) set_music_volume(music_handler.current_volume);

    // if the music player is muted, then pause the music, if it isn't muted, then play the music
    (music_handler.is_muted) ? pause_music() : resume_music();
}

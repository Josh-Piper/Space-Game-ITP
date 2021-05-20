#include "music_player.h"
#include "splashkit.h"

const double MUSIC_MINIMUM_VOLUME = 0.0;
const double MUSIC_MAXIMUM_VOLUME = 1.1;
const double MUSIC_VOLUME_INCREMENT = 0.1;

bool is_music_new_increase_volume_valid(float volume) { return ( ( volume += MUSIC_VOLUME_INCREMENT ) <= MUSIC_MAXIMUM_VOLUME); }; 

bool is_music_new_decrease_volume_valid(float volume) { return ( ( volume -= MUSIC_MINIMUM_VOLUME ) >= MUSIC_MINIMUM_VOLUME); } 

void increase_music_volume(music_handler_data &music_player) 
{ 
    if ( is_music_new_increase_volume_valid ( music_player.current_volume ) ) 
    {
        music_player.current_volume += 0.1; 
        music_player.changed_volume_required = true;
    }
}

void decrease_music_volume(music_handler_data &music_player) 
{ 
    if ( is_music_new_decrease_volume_valid ( music_player.current_volume ) )
    {
        music_player.current_volume -= 0.1; 
        music_player.changed_volume_required = true;
    }
}

void handle_music_pausing(music_handler_data &music_player)
{
    if (music_player.is_muted) 
    {
        music_player.is_muted = false;
    } 
    else
    {
        music_player.is_muted = true;
    }
}

std::string get_current_volume_as_percentage(music_handler_data &music_player) 
{
    string current_volume_to_string { std::to_string(music_player.current_volume).substr(0, 3) }; 
    if (current_volume_to_string == "1.0") return "100%";
    if (current_volume_to_string == "0.0") return "0%";
    return current_volume_to_string.substr(2, 1).append("0%"); // return the percentage as the last 2 decimals, i.e. 0.35 -> 35%
}

music_handler_data create_music_handler()
{
    static const string INIT_FAKE_SONG = "music0";
    static const float DEFAULT_VOLUME = 0.0f;

    music_handler_data music_handler;
    music_handler.current_song = INIT_FAKE_SONG; 
    music_handler.current_volume = DEFAULT_VOLUME; 
    music_handler.changed_volume_required = false;
    music_handler.is_muted = false;
    return music_handler;
}

int get_next_song_number(string original_number) 
{
    static const int MAX_SONGS = 5;
    int current_song_number { std::stoi(original_number) }, new_song_number;    

    if (current_song_number + 1 < MAX_SONGS) 
    {
        new_song_number = current_song_number + 1;
    }
    else
    {
        new_song_number = 1;
    } 

    return new_song_number;
}


string return_next_song(string current_song) 
{
    string current_number {current_song.substr(current_song.length() - 1, 1)};
    string new_song {std::to_string(get_next_song_number(current_number))};
    return current_song.substr(0, current_song.length() - 1).append(new_song);
}

void handle_music(music_handler_data &music_handler) 
{   

    if ( ! music_playing() ) 
    {
        music_handler.current_song = return_next_song(music_handler.current_song);
        fade_music_in(music_handler.current_song, 3000);
        set_music_volume(music_handler.current_volume);
    }

    if (music_handler.changed_volume_required) set_music_volume(music_handler.current_volume);

    (music_handler.is_muted) ? pause_music() : resume_music();
}

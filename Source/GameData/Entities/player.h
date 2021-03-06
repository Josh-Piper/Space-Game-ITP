#ifndef LOST_IN_SPACE_PLAYER
#define LOST_IN_SPACE_PLAYER

#include "splashkit.h"
#include <vector>

using namespace std;

#define PLAYER_SPEED 1.5
#define PLAYER_ROTATE_SPEED 3
#define SCREEN_BORDER 100

/**
 * Different options for the kind of ship.
 * Adjusts the image used.
 */
enum ship_kind
{
    AQUARII,
    GLIESE,
    PEGASI
};

/**
 * The player data keeps track of all of the information related to the player.
 * @field                                          player_sprite       The player's sprite - used to track position and movement
 * @field                                          score               The current score for the player
 * @field                                          kind                Current kind of player ship
 * @field                                          fuel_pct            Handles the drawing of the fuel capacity
 * @field                                          total_power_ups     The total power ups collected
 * @field                                          current_power_up    Bitmap to draw the current powerup the user has
 * @field                                          invincible          Handles the user's infinite health or not
 */
struct player_data
{
    sprite      player_sprite;
    int         score;
    ship_kind   kind;
    double      fuel_pct;
    int         total_power_ups;
    bitmap      current_power_up;
    bool        invincible;
    double      power_up_counter;
};

/**
 * The ship bitmap function converts a ship kind into a 
 * bitmap that can be used.
 * 
 * Not exposed by the header.
 * 
 * @param                                          kind  
 * @return      The bitmap matching this ship kind
 */
bitmap ship_bitmap(ship_kind kind);

/**
 * Creates a new player in the centre of the screen with the default ship.
 * 
 * @returns     The new player data
 */
player_data new_player();

/**
 * Increment the player's power up count
 * @param                                          player
 */ 
void increment_player_power_up_count(player_data &player);

/**
 * Change the player's current power up bitmap image
 * @param                                          player
 * @param                                          new_powerup_bitmap
 */ 
void set_player_current_power_up_image(player_data &player, bitmap new_bitmap);

/**
 * Draws the player to the screen. 
 * @param                                          player_to_draw  
 */
void draw_player(const player_data &player_to_draw);

/**
 * Update the players camera angle depending on the dimensions of the map
 * @param                                          player_to_update
 */ 
void update_player_camera(player_data &player_to_update);

/**
 * Update the player's current fuel
 * @param                                          fuel_pct
 */ 
void update_fuel(double &fuel_pct);

/**
 * Actions a step update of the player - moving them and adjusting the camera.
 * @param                                          player_to_update     
 */
void update_player(player_data &player_to_update);

/**
 * Apply the fuel power up to a player
 * @param                                          player
 */ 
void apply_fuel_power_up_to_player(player_data &player);

/**
 * Apply the shield power up to a player
 * @param                                          player
 */ 
void apply_shield_power_up_to_player(player_data &player);

/**
 * Apply the potion power up to a player
 * @param                                          player
 */ 
void apply_potion_power_up_to_player(player_data &player);

/**
 * Apply the drops power up to a player
 * @param                                          player
 */ 
void apply_drops_power_up_to_player(player_data &player);

/**
 * Apply the diamond power up to a player
 * @param                                          player
 */ 
void apply_diamond_power_up_to_player(player_data &player);

/**
 * Apply the coin power up to a player
 * @param                                          player
 */ 
void apply_coin_power_up_to_player(player_data &player);

/**
 * Read user input and update the player based on this interaction.
 * @param                                          player    
 */
void handle_input(player_data &player);

#endif
#ifndef BULLET
#define BULLET

#include "splashkit.h"
#include <vector>
#include <functional>

/**
 * A bullet that entities can shoot and use
 * @field                                          original_location
 * @field                                          bullet_sprite
 */ 
struct bullet
{
    point_2d                                       original_location;
    sprite                                         bullet_sprite;
};

/**
 * Create a bullet dependent on the rotation of the bullets creator
 * @param                                          x
 * @param                                          y
 * @param                                          rotation
 */ 
bullet new_bullet(double x, double y, float rotation);

/**
 * Delete a bullet from a vector of bullets based on the id
 * @param                                          bullets
 * @param                                          id
 */ 
void delete_bullet(vector<bullet> &bullets, int id);

/**
 * Draw a bullet
 * @param                                          bullet
 */ 
void draw_bullet(const bullet &bullet);

/**
 * Update the bullet
 * @param                                          bullet
 */ 
void update_bullet(const bullet &bullet);

/**
 * Update the bullet's location depending on the rotation of the space_fighter
 * @param                                          bullet
 */ 
void update_bullet_location(bullet &bullet);



#endif
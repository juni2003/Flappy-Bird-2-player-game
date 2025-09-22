/**
 * @file Pipe.cpp
 * @brief Implementation of the Pipe class for Flappy Bird 2-player game
 * 
 * This file contains the implementation of pipe obstacles that move across
 * the screen. Pipes consist of upper and lower segments with a gap between
 * them for birds to navigate through.
 */

#include "Pipe.h"
#include "Globals.h"

using namespace sf;

// Static member definitions
Texture Pipe::pipe_down, Pipe::pipe_up;          ///< Shared textures for all pipe instances
int Pipe::pipe_distance = 170;                   ///< Vertical gap between pipe segments (pixels)
int Pipe::move_speed = 400;                      ///< Horizontal movement speed (pixels per second)

/**
 * @brief Constructor - creates a pipe pair at specified vertical position
 * @param y_pos Vertical position for the center of the pipe gap
 * 
 * Creates upper and lower pipe segments with appropriate positioning
 * and scaling. The gap between pipes allows birds to pass through.
 */
Pipe::Pipe(int y_pos)
{
    // Setup lower pipe segment
    sprite_down.setTexture(pipe_down);
    sprite_down.setScale(scaling_factor, scaling_factor);
    
    // Setup upper pipe segment  
    sprite_up.setTexture(pipe_up);
    sprite_up.setScale(scaling_factor, scaling_factor);
    
    // Position upper pipe at specified height
    sprite_up.setPosition(window_width, y_pos);
    
    // Position lower pipe with gap between them
    sprite_down.setPosition(window_width, 
                           y_pos - pipe_distance - sprite_up.getGlobalBounds().height);
}

/**
 * @brief Updates pipe position based on movement speed
 * @param dt Delta time for frame-independent movement
 * 
 * Moves both pipe segments leftward across the screen at constant speed.
 * Pipes will be removed when they move off the left edge of the screen.
 */
void Pipe::update(sf::Time& dt)
{
    // Move both pipe segments leftward
    sprite_up.move(-move_speed * dt.asSeconds(), 0.f);
    sprite_down.move(-move_speed * dt.asSeconds(), 0.f);
}

/**
 * @brief Loads pipe textures from asset files (called once for all pipes)
 * 
 * Loads the texture files for upper and lower pipe segments.
 * This is a static method called once during game initialization.
 */
void Pipe::loadTextures()
{
    pipe_down.loadFromFile("assets/pipedown.png");  // Lower pipe segment texture
    pipe_up.loadFromFile("assets/pipe.png");        // Upper pipe segment texture
}

/**
 * @brief Gets the right boundary of the pipe for collision detection
 * @return X-coordinate of the right edge of the pipe's collision box
 * 
 * Used for collision detection with birds and for determining when
 * birds have successfully passed through the pipe gap.
 */
float Pipe::getRightBound()
{
    return sprite_down.getGlobalBounds().left + 
           sprite_down.getGlobalBounds().width;
}
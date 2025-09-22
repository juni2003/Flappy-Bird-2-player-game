/**
 * @file Bird.cpp
 * @brief Implementation of the Bird class for Flappy Bird 2-player game
 * 
 * This file contains the implementation of bird physics, animation,
 * and collision detection for both player birds in the game.
 */

#include "Bird.h"
#include "Globals.h"

using namespace sf;

/**
 * @brief Constructor - initializes bird physics constants and loads textures
 * 
 * Sets up gravity, flap speed, animation variables, and loads all bird
 * textures for both players. Initializes both bird sprites and positions.
 */
Bird::Bird() :
gravity(14),        // Gravitational acceleration (pixels per second squared)
birdflapspeed(300), // Upward velocity applied when flapping
animation(0),       // Animation frame counter
animation_switch(0), // Current animation frame (0 or 1)
birdfly(false)      // Physics disabled initially
{
    // Load textures for Player 1 bird (down and up wing positions)
    bird1[0].loadFromFile("assets/bird1down.png");
    bird1[1].loadFromFile("assets/bird1up.png");
    
    // Load textures for Player 2 bird (down and up wing positions)
    bird2[0].loadFromFile("assets/bird2down.png");
    bird2[1].loadFromFile("assets/bird2up.png");
    
    // Setup Player 1 bird sprite
    bird1_sprite.setTexture(bird1[0]);
    bird1_sprite.setScale(scaling_factor, scaling_factor);
    
    // Setup Player 2 bird sprite
    bird2_sprite.setTexture(bird2[0]);
    bird2_sprite.setScale(scaling_factor, scaling_factor);
    
    // Set initial positions for both birds
    bird1_resetPosition();
    bird2_resetPosition();
}

/**
 * @brief Updates Player 1's bird physics and animation
 * @param dt Delta time for frame-independent movement
 * 
 * Handles gravity application, sprite animation (wing flapping),
 * vertical movement, and boundary checking for Player 1's bird.
 */
void Bird::update1(Time& dt)
{
    // Only update if bird is above ground and physics are enabled
    if (bird1_sprite.getGlobalBounds().top < 548 && birdfly)
    {
        // Handle wing flapping animation (changes texture every 5 frames)
        if (animation == 5)
        {
            bird1_sprite.setTexture(bird1[animation_switch]);
            // Toggle between wing up and wing down textures
            if (animation_switch) 
                animation_switch = 0;
            else 
                animation_switch = 1;
            animation = 0;
        }
        
        animation++;
        
        // Apply gravity to vertical velocity
        velocity += gravity * dt.asSeconds();
        
        // Move bird vertically based on current velocity
        bird1_sprite.move(0, velocity);
        
        // Prevent bird from going above screen top
        if (bird1_sprite.getGlobalBounds().top < 0)
            bird1_sprite.setPosition(100, 0);
    }
}

/**
 * @brief Updates Player 2's bird physics and animation
 * @param dt Delta time for frame-independent movement
 * 
 * Handles gravity application, sprite animation (wing flapping),
 * vertical movement, and boundary checking for Player 2's bird.
 */
void Bird::update2(Time& dt)
{
    // Only update if bird is above ground and physics are enabled
    if (bird2_sprite.getGlobalBounds().top < 548 && birdfly)
    {
        // Handle wing flapping animation (changes texture every 5 frames)
        if (animation == 5)
        {
            bird2_sprite.setTexture(bird2[animation_switch]);
            // Toggle between wing up and wing down textures
            if (animation_switch) 
                animation_switch = 0;
            else 
                animation_switch = 1;
            animation = 0;
        }
        
        animation++;
        
        // Apply gravity to vertical velocity
        velocity += gravity * dt.asSeconds();
        
        // Move bird vertically based on current velocity
        bird2_sprite.move(0, velocity);
        
        // Prevent bird from going above screen top
        if (bird2_sprite.getGlobalBounds().top < 0)
            bird2_sprite.setPosition(100, 0);
    }
}

/**
 * @brief Applies upward flapping force to the bird
 * @param dt Delta time for frame-independent movement
 * 
 * Sets the bird's velocity to negative (upward) value when player
 * presses the flap key, counteracting gravity.
 */
void Bird::birdflap(Time& dt)
{
    // Apply upward velocity (negative because Y increases downward)
    velocity = -birdflapspeed * dt.asSeconds();
}

/**
 * @brief Gets the right boundary of Player 1's bird for collision detection
 * @return X-coordinate of the right edge of the bird's collision box
 * 
 * Used for pipe collision detection and score monitoring.
 */
float Bird::getRightBound()
{
    return bird1_sprite.getGlobalBounds().left + 
           bird1_sprite.getGlobalBounds().width;
}

/**
 * @brief Resets Player 1's bird to starting position and state
 * 
 * Places Player 1's bird at the initial position and resets velocity.
 * Used when starting a new game or restarting after collision.
 */
void Bird::bird1_resetPosition()
{
    bird1_sprite.setPosition(100, 50);  // Starting position for Player 1
    velocity = 0;                       // Reset vertical velocity
}

/**
 * @brief Resets Player 2's bird to starting position and state
 * 
 * Places Player 2's bird at the initial position and resets velocity.
 * Used when starting a new game or restarting after collision.
 */
void Bird::bird2_resetPosition()
{
    bird2_sprite.setPosition(100, 150); // Starting position for Player 2 (below Player 1)
    velocity = 0;                       // Reset vertical velocity
}

/**
 * @brief Controls whether bird physics should be active
 * @param should_fly True to enable physics and movement, false to disable
 * 
 * Used to start/stop bird physics when game begins or ends.
 */
void Bird::birdshouldfly(bool should_fly)
{
    this->birdfly = should_fly;
}

/**
 * @file Bird.h
 * @brief Header file for the Bird class in Flappy Bird 2-player game
 * 
 * This file defines the Bird class which handles the physics, animation,
 * and rendering for both player birds in the game. Each bird has its own
 * sprite, animation state, and collision boundaries.
 */

#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

/**
 * @class Bird
 * @brief Represents a bird character in the Flappy Bird game
 * 
 * The Bird class manages bird physics (gravity, flapping), sprite animation
 * (alternating between up/down wing positions), and provides collision
 * detection boundaries. Supports two separate birds for 2-player gameplay.
 */
class Bird
{
private:
    Texture bird1[2];        ///< Textures for Player 1 bird (down and up wing positions)
    Texture bird2[2];        ///< Textures for Player 2 bird (down and up wing positions)
    const int gravity;       ///< Gravitational acceleration affecting bird fall speed
    const int birdflapspeed; ///< Upward velocity applied when bird flaps
    float velocity;          ///< Current vertical velocity of the bird
    int animation;           ///< Animation frame counter for wing flapping
    int animation_switch;    ///< Current animation frame (0 or 1 for wing position)
    bool birdfly;           ///< Flag indicating whether bird physics are active

public:
    Sprite bird1_sprite;    ///< Sprite for Player 1's bird
    Sprite bird2_sprite;    ///< Sprite for Player 2's bird

    /**
     * @brief Constructor - initializes bird textures, sprites, and physics constants
     */
    Bird();

    /**
     * @brief Controls whether bird physics should be active
     * @param should_fly True to enable physics, false to disable
     */
    void birdshouldfly(bool should_fly);

    /**
     * @brief Applies upward flapping force to the bird
     * @param dt Delta time for frame-independent movement
     */
    void birdflap(Time& dt);

    /**
     * @brief Resets Player 1's bird to starting position
     */
    void bird1_resetPosition();

    /**
     * @brief Resets Player 2's bird to starting position  
     */
    void bird2_resetPosition();

    /**
     * @brief Updates Player 1's bird physics and animation
     * @param dt Delta time for frame-independent movement
     */
    void update1(Time& dt);

    /**
     * @brief Updates Player 2's bird physics and animation
     * @param dt Delta time for frame-independent movement
     */
    void update2(Time& dt);

    /**
     * @brief Gets the right boundary of Player 1's bird for collision detection
     * @return X-coordinate of the right edge of the bird's collision box
     */
    float getRightBound();
};
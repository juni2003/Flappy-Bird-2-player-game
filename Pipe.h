/**
 * @file Pipe.h
 * @brief Header file for the Pipe class in Flappy Bird 2-player game
 * 
 * This file defines the Pipe class which creates the obstacle pipes that
 * birds must navigate through. Each pipe consists of an upper and lower
 * segment with a gap between them for birds to pass through.
 */

#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

/**
 * @class Pipe
 * @brief Represents a pipe obstacle in the Flappy Bird game
 * 
 * The Pipe class manages pipe textures, positioning, movement, and collision
 * boundaries. Pipes move from right to left across the screen and are
 * spawned at random vertical positions to create varied difficulty.
 */
class Pipe
{
private:
    static Texture pipe_down, pipe_up;  ///< Static textures shared by all pipe instances
    static int pipe_distance;           ///< Vertical gap between upper and lower pipe segments

public:
    /**
     * @brief Constructor - creates a pipe pair at specified vertical position
     * @param y_pos Vertical position for the pipe gap center
     */
    Pipe(int y_pos);

    Sprite sprite_up, sprite_down;      ///< Sprites for upper and lower pipe segments
    static int move_speed;              ///< Horizontal movement speed of pipes (pixels per second)

    /**
     * @brief Loads pipe textures from asset files (called once for all pipes)
     */
    static void loadTextures();

    /**
     * @brief Updates pipe position based on movement speed
     * @param dt Delta time for frame-independent movement
     */
    void update(Time& dt);

    /**
     * @brief Gets the right boundary of the pipe for collision detection
     * @return X-coordinate of the right edge of the pipe's collision box
     */
    float getRightBound();
};
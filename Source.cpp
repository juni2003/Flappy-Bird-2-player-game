/**
 * @file Source.cpp 
 * @brief Entry point for the Flappy Bird 2-player game
 * 
 * Creates the main game window and starts the game loop.
 * This file serves as the main entry point for the application.
 */

#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Game.h"

using namespace sf;

/**
 * @brief Main function - program entry point
 * @return 0 on successful execution
 * 
 * Creates the game window with dimensions from Globals.h and
 * initializes the main game loop.
 */
int main()
{
    RenderWindow win(VideoMode(window_width, window_height), "Flappy Bird");  // Fixed: string literal was split across lines
    Game game(win);
    game.startGameLoop();
    return 0;
}

/**
 * @file Game.h
 * @brief Header file for the main Game class in Flappy Bird 2-player game
 * 
 * This file defines the Game class which orchestrates all game systems
 * including rendering, input handling, collision detection, scoring,
 * and game state management for a two-player Flappy Bird experience.
 */

#pragma once
#include <SFML/Graphics.hpp>
#include "Bird.h"
#include <vector>
#include "Pipe.h"
#include <random>

using namespace sf;

/**
 * @class Game
 * @brief Main game controller class that manages all game systems
 * 
 * The Game class handles the complete game lifecycle including menu screens,
 * gameplay mechanics, collision detection, scoring, and rendering. It manages
 * two bird players, dynamic pipe generation, and multiple game states.
 */
class Game
{
private:
    // Window reference (must be first to match initialization order)
    RenderWindow& win;                          ///< Reference to the main game window
    
    // Menu and UI textures/sprites
    Texture menu_texture, controls_texture;     ///< Textures for menu and controls screens
    Sprite menu_sprite, controls_sprite;        ///< Sprites for menu and controls screens
    
    // Background and environment
    Texture background, ground_texture;         ///< Background and ground textures
    Sprite background_sprite, ground_sprite1, ground_sprite2;  ///< Background and scrolling ground sprites
    
    // Player birds
    Bird bird1;                                 ///< Player 1's bird object
    Bird bird2;                                 ///< Player 2's bird object
    
    // Game state flags
    bool enter_pressed;                         ///< Flag indicating if game has started
    bool run_game1, run_game2;                 ///< Flags indicating if each player is still active
    bool start_monitoring;                      ///< Flag for score monitoring through pipes
    bool bird1Collided;                         ///< Flag indicating Player 1's bird has collided
    bool bird2Collided;                         ///< Flag indicating Player 2's bird has collided
    bool showMainMenu;                          ///< Flag for displaying main menu
    bool showControls;                          ///< Flag for displaying controls screen
    
    // Movement and physics
    const int move_speed = 270;                 ///< Horizontal movement speed for ground/pipes
    
    // Victory sprites
    Texture bird1_win_texture;                  ///< Texture for Player 2 victory sprite
    Sprite bird1_win_sprite;                    ///< Sprite for Player 2 victory display
    Texture bird2_win_texture;                  ///< Texture for Player 1 victory sprite  
    Sprite bird2_win_sprite;                    ///< Sprite for Player 1 victory display
    
    // Pipe system
    int pipe_counter, pipe_spawn_time;          ///< Timing variables for pipe spawning
    int score_p1, score_p2;                    ///< Player scores
    std::vector<Pipe> pipes;                    ///< Container for active pipe obstacles
    std::random_device rd;                      ///< Random device for pipe positioning
    std::uniform_int_distribution<int> dist{250, 550};  ///< Random distribution for pipe heights
    
    // Text and fonts
    Font normalfont;                            ///< Font for regular UI text
    Font gamefont;                              ///< Font for game title and headers
    Text playagain_text, player1_score_text, player2_score_text;  ///< Score and restart text
    Text p1_win_text, p2_win_text, Draw_text;  ///< Victory and draw message text
    Texture go_texture;                         ///< Game over screen texture
    Sprite go_sprite;                           ///< Game over screen sprite

    // Private methods for game logic
    
    /**
     * @brief Renders all game objects to the screen
     */
    void draw();
    
    /**
     * @brief Moves ground sprites to create scrolling effect
     * @param dt Delta time for frame-independent movement
     */
    void moveGround(Time& dt);
    
    /**
     * @brief Processes core game logic during active gameplay
     * @param dt Delta time for frame-independent updates
     */
    void doProcessing(Time& dt);
    
    /**
     * @brief Displays the main menu screen
     */
    void showMainMenuScreen();
    
    /**
     * @brief Transitions to the main game screen
     */
    void showGameScreen();
    
    /**
     * @brief Displays the controls instruction screen
     */
    void showControlsScreen();
    
    /**
     * @brief Checks collision detection for Player 1's bird
     */
    void checkCollisions1();
    
    /**
     * @brief Checks collision detection for Player 2's bird
     */
    void checkCollisions2();
    
    /**
     * @brief Resets game state for a new game session
     */
    void restartGame();
    
    /**
     * @brief Updates player scores when passing through pipes
     */
    void checkScore();
    
    /**
     * @brief Converts integer to string for score display
     * @param num Integer value to convert
     * @return String representation of the number
     */
    std::string toString(int num);

public:
    /**
     * @brief Constructor - initializes all game systems and assets
     * @param window Reference to the SFML RenderWindow for rendering
     */
    Game(RenderWindow& window);
    
    /**
     * @brief Main game loop that handles events, updates, and rendering
     */
    void startGameLoop();
};

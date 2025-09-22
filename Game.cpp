/**
 * @file Game.cpp
 * @brief Implementation of the main Game class for Flappy Bird 2-player game
 * 
 * This file contains the core game logic, rendering, collision detection,
 * and event handling for a two-player Flappy Bird game built with SFML.
 */

#include "Game.h"
#include "Globals.h"
#include <iostream>  // Fixed: was <stream>
#include <SFML/Audio.hpp>  // Fixed: was <SFMI/Audio.hpp>
#include <sstream>  // Added for toString method

using namespace sf;

/**
 * @brief Constructor for the Game class
 * @param window Reference to the SFML RenderWindow for rendering
 * 
 * Initializes all game components including sprites, textures, fonts,
 * and sets up the initial game state for both players.
 */
Game::Game(RenderWindow& window) : win(window),
enter_pressed(false),
run_game1(true),
run_game2(true),
start_monitoring(false),
bird1Collided(false),  // Fixed: was birdICollided
bird2Collided(false),
showMainMenu(true),
showControls(false),
pipe_counter(71),
pipe_spawn_time(70),
score_p1(0),
score_p2(0)
{
    win.setFramerateLimit(60); // Setting frames per seconds

    // Setting Main menu screen
    menu_texture.loadFromFile("assets/mainmenu.png");
    menu_sprite.setTexture(menu_texture);
    menu_sprite.setScale(3.3, 2.8);
    menu_sprite.setPosition(0.f, 0.f);
    
    // Setting Show Controls screen
    controls_texture.loadFromFile("assets/controls.png");
    controls_sprite.setTexture(controls_texture);
    controls_sprite.setScale(1.5, 1.1);
    controls_sprite.setPosition(0.f, 0.f);
    
    // Background Setup
    background.loadFromFile("assets/bg.png");
    background_sprite.setTexture(background);
    background_sprite.setScale(2.3, 2);
    background_sprite.setPosition(0.f, -250.f);
    
    // Loading and setting ground
    ground_texture.loadFromFile("assets/ground.png");
    ground_sprite1.setTexture(ground_texture);
    ground_sprite2.setTexture(ground_texture);
    
    // Scaling ground
    ground_sprite1.setScale(scaling_factor, scaling_factor);
    ground_sprite2.setScale(scaling_factor, scaling_factor);
    
    // Setting ground position
    ground_sprite1.setPosition(0, 578);
    ground_sprite2.setPosition(ground_sprite1.getGlobalBounds().width, 578);  // Fixed: was getGlobalBounds(),width
    
    // Loading normal and game font to use
    normalfont.loadFromFile("assets/mono.ttf");
    gamefont.loadFromFile("assets/gamefont.ttf");
    
    // Restart game text setting
    playagain_text.setFont(gamefont);
    playagain_text.setCharacterSize(65);
    playagain_text.setFillColor(Color::Black);
    playagain_text.setPosition(40, 650);
    playagain_text.setString("Press R to Restart Game");
    
    // Player 1 Score text setting
    player1_score_text.setFont(normalfont);
    player1_score_text.setCharacterSize(25);
    player1_score_text.setFillColor(Color::Magenta);
    player1_score_text.setPosition(15, 15);
    player1_score_text.setString("Player 1: 0");
    
    // Player 2 Score setting
    player2_score_text.setFont(normalfont);
    player2_score_text.setCharacterSize(25);
    player2_score_text.setFillColor(Color(139, 69, 19));
    player2_score_text.setPosition(410, 15);
    player2_score_text.setString("Player 2: 0");

    // Player1 Wins text setting
    p1_win_text.setFont(gamefont);
    p1_win_text.setCharacterSize(80);
    p1_win_text.setFillColor(Color::Magenta);
    p1_win_text.setPosition(130, 450);
    p1_win_text.setString("Player 1 Wins");
    
    // Player2 Wins text setting
    p2_win_text.setFont(gamefont);
    p2_win_text.setCharacterSize(80);
    p2_win_text.setFillColor(Color(139, 69, 19));
    p2_win_text.setPosition(130, 450);
    p2_win_text.setString("Player 2 Wins");
    
    // Game Draw text setting
    Draw_text.setFont(gamefont);
    Draw_text.setCharacterSize(80);
    Draw_text.setFillColor(Color::White);
    Draw_text.setPosition(130, 450);
    Draw_text.setString("Game Draw");
    
    // Game over image setting
    go_texture.loadFromFile("assets/gameover.png");
    go_sprite.setTexture(go_texture);
    go_sprite.setScale(scaling_factor, scaling_factor);
    go_sprite.setPosition(160, 250);
    
    // Bird 1 win pic
    bird1_win_texture.loadFromFile("assets/bird1_win.png");
    bird1_win_sprite.setTexture(bird1_win_texture);
    bird1_win_sprite.setScale(2.0f, 2.0f);
    bird1_win_sprite.setPosition(250.f, 400.f);
    
    // Bird 2 win pic
    bird2_win_texture.loadFromFile("assets/bird2_win.png");
    bird2_win_sprite.setTexture(bird2_win_texture);
    bird2_win_sprite.setScale(2.0f, 2.0f);
    bird2_win_sprite.setPosition(250.f, 400.f);

    Pipe::loadTextures();
}

/**
 * @brief Processes game logic during active gameplay
 * @param dt Delta time for frame-independent movement
 * 
 * Handles ground movement, pipe spawning, collision detection,
 * and score tracking when the game is active.
 */
void Game::doProcessing(Time& dt)
{
    if (enter_pressed)
    {
        moveGround(dt);
        
        // Spawn new pipes at regular intervals
        if (pipe_counter > pipe_spawn_time)
        {
            pipes.push_back(Pipe(dist(rd)));
            pipe_counter = 0;
        }
        pipe_counter++;
        
        // Update existing pipes and remove off-screen ones
        for (size_t i = 0; i < pipes.size(); i++)  // Fixed: use size_t to avoid signed/unsigned comparison warning
        {
            pipes[i].update(dt);
            if (pipes[i].getRightBound() < 0)
            {
                pipes.erase(pipes.begin() + i);
                i--; // Decrement i since we removed an element
            }
        }
        
        checkCollisions1();
        checkCollisions2();
        checkScore();
    }

    // Update both birds
    bird1.update1(dt);
    bird2.update2(dt);
}

/**
 * @brief Main game loop that handles events, updates, and rendering
 * 
 * Displays the main menu, then enters the main game loop where it
 * processes events, updates game state, and renders everything to screen.
 */
void Game::startGameLoop()
{
    Clock clock;

    // Display the main menu screen
    showMainMenuScreen();
    
    // Game Loop
    while (win.isOpen())
    {
        Time dt = clock.restart();
        Event event;
        
        // Event Loop
        while (win.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                win.close();
            }
            
            if (event.type == Event::KeyPressed && (run_game1 || run_game2))
            {
                if (event.key.code == Keyboard::Enter && !enter_pressed)  // Fixed: was lenter_pressed
                {
                    enter_pressed = true;
                    bird1.birdshouldfly(true);  // Fixed: was bindshouldfly
                    bird2.birdshouldfly(true);  // Fixed: was bindshouldfly
                }
                if (event.key.code == Keyboard::Space && enter_pressed)
                {
                    bird1.birdflap(dt);  // Fixed: was bindflap
                }
                if (event.key.code == Keyboard::Up && enter_pressed)
                {
                    bird2.birdflap(dt);  // Fixed: was bindflap
                }
            }
            
            // Restart game logic
            if (event.type == Event::KeyPressed && (!run_game1 || !run_game2))  // Fixed: was (|run_game1 || |run_game2)
            {
                if (event.key.code == Keyboard::R && (!run_game1 || !run_game2))  // Fixed: was (|run_game1 ||!run_game2)
                {
                    restartGame();
                }
            }
        }
        
        if (enter_pressed)
        {
            doProcessing(dt);
        }
        
        draw();

        // Display the window
        win.display();
    }
}

/**
 * @brief Displays the main menu screen and waits for user input
 */
void Game::showMainMenuScreen()
{
    // Set the flag to show the main menu and hide other screens
    showMainMenu = true;
    showControls = false;

    // Clear the window and draw the main menu screen
    win.clear();
    win.draw(menu_sprite);
    win.display();

    // Wait for a key press to proceed to the control screen
    Event event;
    while (win.waitEvent(event))
    {
        if (event.type == Event::KeyPressed)
        {
            // Proceed to the control screen
            showControlsScreen();
            break;
        }
    }
}

/**
 * @brief Displays the controls screen and waits for user input
 */
void Game::showControlsScreen()
{
    // Set the flag to show the controls screen
    showMainMenu = false;
    showControls = true;

    // Clear the window and draw the controls screen
    win.clear();
    win.draw(controls_sprite);
    win.display();

    // Wait for a key press to proceed to the game screen
    Event event;
    while (win.waitEvent(event))
    {
        if (event.type == Event::KeyPressed)
        {
            // Proceed to the game screen
            showGameScreen();
            break;
        }
    }
}

/**
 * @brief Transitions to the game screen and starts gameplay
 */
void Game::showGameScreen()
{
    // Set the flag to start the game and hide the main menu and controls screens
    showMainMenu = false;
    showControls = false;
    restartGame();
}

/**
 * @brief Checks collision detection for Player 1's bird
 * 
 * Detects collisions with pipes and ground boundaries.
 * Sets bird1Collided flag and stops player 1's game on collision.
 */
void Game::checkCollisions1()
{
    if (pipes.size() > 0)
    {
        if (pipes[0].sprite_down.getGlobalBounds().intersects(bird1.bird1_sprite.getGlobalBounds()) ||
            pipes[0].sprite_up.getGlobalBounds().intersects(bird1.bird1_sprite.getGlobalBounds()) ||
            bird1.bird1_sprite.getGlobalBounds().top >= 540)
        {
            enter_pressed = false;
            run_game1 = false;
            bird1Collided = true;
        }
    }
}

/**
 * @brief Checks collision detection for Player 2's bird
 * 
 * Detects collisions with pipes and ground boundaries.
 * Sets bird2Collided flag and stops player 2's game on collision.
 */
void Game::checkCollisions2()
{
    if (pipes.size() > 0)
    {
        if (pipes[0].sprite_down.getGlobalBounds().intersects(bird2.bird2_sprite.getGlobalBounds()) ||
            pipes[0].sprite_up.getGlobalBounds().intersects(bird2.bird2_sprite.getGlobalBounds()) ||
            bird2.bird2_sprite.getGlobalBounds().top >= 540)
        {
            enter_pressed = false;
            run_game2 = false;
            bird2Collided = true;
        }
    }
}

/**
 * @brief Tracks and updates player scores when passing through pipes
 * 
 * Uses a monitoring system to detect when birds pass through pipe gaps
 * and increments the appropriate player's score.
 */
void Game::checkScore()
{
    if (pipes.size() > 0)
    {
        if (!start_monitoring)
        {
            // Start monitoring when birds enter the pipe gap
            if (bird1.bird1_sprite.getGlobalBounds().left >
                pipes[0].sprite_down.getGlobalBounds().left &&
                bird1.getRightBound() < pipes[0].getRightBound())
            {
                start_monitoring = true;
            }
            if (bird2.bird2_sprite.getGlobalBounds().left >
                pipes[0].sprite_down.getGlobalBounds().left &&
                bird2.getRightBound() < pipes[0].getRightBound())
            {
                start_monitoring = true;
            }
        }
        else
        {
            // Award points when birds exit the pipe gap
            if (bird1.bird1_sprite.getGlobalBounds().left >
                pipes[0].getRightBound())
            {
                score_p1++;
                player1_score_text.setString("Player 1: " + toString(score_p1));
                start_monitoring = false;
            }
            if (bird2.bird2_sprite.getGlobalBounds().left >
                pipes[0].getRightBound())
            {
                score_p2++;
                player2_score_text.setString("Player 2: " + toString(score_p2));
                start_monitoring = false;
            }
        }
    }
}

/**
 * @brief Renders all game objects to the screen
 * 
 * Draws background, pipes, ground, birds (based on game state),
 * score text, and game over/victory screens as appropriate.
 */
void Game::draw()
{
    win.clear();
    win.draw(background_sprite);
    
    // Draw all pipes
    for (Pipe& pipe : pipes)
    {
        win.draw(pipe.sprite_down);
        win.draw(pipe.sprite_up);
    }
    
    win.draw(ground_sprite1);
    win.draw(ground_sprite2);

    // Draw birds based on game state
    if (run_game1 && run_game2) // Both birds are still alive - draw both
    {
        win.draw(bird1.bird1_sprite);
        win.draw(bird2.bird2_sprite);
    }
    else if (run_game1 && !run_game2) // Bird2 collided, bird1 is still alive
    {
        win.draw(bird1.bird1_sprite);
        win.draw(bird2_win_sprite); // Show Player 1 victory message
    }
    else if (!run_game1 && run_game2) // Bird1 collided, bird2 is still alive  
    {
        win.draw(bird2.bird2_sprite);
        win.draw(bird1_win_sprite); // Show Player 2 victory message
    }

    // Draw score displays
    win.draw(player1_score_text);
    win.draw(player2_score_text);

    // Draw game over screens based on game state
    if (!run_game1 && !run_game2) // Both birds collided - draw
    {
        win.draw(go_sprite);
        win.draw(playagain_text);
        win.draw(Draw_text);
    }
    else if (!run_game1) // Player 1 lost - Player 2 wins
    {
        win.draw(go_sprite);
        win.draw(playagain_text);
        win.draw(p2_win_text);
    }
    else if (!run_game2) // Player 2 lost - Player 1 wins
    {
        win.draw(go_sprite);
        win.draw(playagain_text);
        win.draw(p1_win_text);
    }
}

/**
 * @brief Moves the ground sprites to create scrolling effect
 * @param dt Delta time for frame-independent movement
 * 
 * Moves both ground sprites leftward and repositions them
 * when they move off-screen to create continuous scrolling.
 */
void Game::moveGround(Time& dt)
{
    ground_sprite1.move(-move_speed * dt.asSeconds(), 0.f);
    ground_sprite2.move(-move_speed * dt.asSeconds(), 0.f);

    if (ground_sprite1.getGlobalBounds().left + ground_sprite1.getGlobalBounds().width < 0)
    {
        ground_sprite1.setPosition(ground_sprite2.getGlobalBounds().left +
                                   ground_sprite2.getGlobalBounds().width, 578);
    }
    if (ground_sprite2.getGlobalBounds().left + ground_sprite2.getGlobalBounds().width < 0)
    {
        ground_sprite2.setPosition(ground_sprite1.getGlobalBounds().left +
                                   ground_sprite1.getGlobalBounds().width, 578);
    }
}

/**
 * @brief Resets the game state for a new game
 * 
 * Resets bird positions, collision flags, scores, and pipe state
 * to start a fresh game session.
 */
void Game::restartGame()
{
    bird1.bird1_resetPosition();
    bird2.bird2_resetPosition();
    bird1.birdshouldfly(false);
    bird2.birdshouldfly(false);

    bird1Collided = false;
    bird2Collided = false;
    run_game1 = true;
    run_game2 = true;
    enter_pressed = false;

    pipe_counter = 71;
    pipes.clear();
    score_p1 = 0;
    score_p2 = 0;
    player1_score_text.setString("Player 1: 0");
    player2_score_text.setString("Player 2: 0");
}

/**
 * @brief Converts an integer to string for display purposes
 * @param num Integer to convert
 * @return String representation of the integer
 */
std::string Game::toString(int num)
{
    std::stringstream ss;
    ss << num;
    return ss.str();
}
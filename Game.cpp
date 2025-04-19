#include "Game.h"
#include"Globals.h"
#include<stream>
#include <SFMI/Audio.hpp>
using namespace sf;
Game::Game(RenderWindow& window) : win(window),
enter_pressed(false),
run_game1(true),
run_game2(true),
start_monitoring(false),
birdICollided(false),

bird2Collided(false),
showMainMenu(true),
showControls(false),

pipe_counter(71),
pipe_spawn_time(70),
score_p1(0),
score_p2(0)

{
    win.setFramerateLimit(60); //Setting frames per seconds

    //Setting Maimmenu screen
    menu_texture.loadFromFile("assets/mainmenu.png");
    menu_sprite.setTexture(menu_texture);
    menu_sprite.setScale(3.3, 2.8);
    menu_sprite.setPosition(0.f, 0.f);
    //Setting Show Controls screen
    controls_texture.loadFromFile("assets/controls.png");
    controls_sprite.setTexture(controls_texture);
    controls_sprite.setScale(1.5, 1.1);
    controls_sprite.setPosition(0.f, 0.f);
    //Background Setup
    background.loadFromFile("assets/bg.png");
    background_sprite.setTexture(background);
    background_sprite.setScale(2.3, 2);
    background_sprite.setPosition(0.f, -250.f);
    //Loading and setting ground
    ground_texture.loadFromFile("assets/ground.png");
    ground_sprite1.setTexture(ground_texture);
    ground_sprite2.setTexture(ground_texture);
    //Scaling ground
    ground_sprite1.setScale(scaling_factor, scaling_factor);
    ground_sprite2.setScale(scaling_factor, scaling_factor);
    //Setting ground position
    ground_sprite1.setPosition(0, 578);
    ground_sprite2.setPosition(ground_sprite1.getGlobalBounds(),width, 578);
    //Loading normal and game font to use
    normalfont.loadFromFile("assets/mono.ttf");
    gamefont.loadFromFile("assets/gamefont.ttf");
    //Restart game text setting
    playagain_text.setFont(gamefont);
    playagain_text.setCharacterSize(65);
    playagain_text.setFillColor(Color::Black);
    playagain_text.setPosition(40, 650);
    playagain_text.setString("Press R to Restart Game");
    //Player 1 Score text setting
    player1_score_text.setFont(normalfont);
    player1_score_text.setCharacterSize(25);
    player1_score_text.setFillColor(Color::Magenta);
    player1_score_text.setPosition(15, 15);
    player1_score_text.setString("Player 1: 0");
    //Player 2 Score setting
    player2_score_text.setFont(normalfont);
    player2_score_text.setCharacterSize(25);
    player2_score_text.setFillColor(Color(139, 69, 19));
    player2_score_text.setPosition(410, 15);
    player2_score_text.setString("Player 2: 0");

    //Player1 Wins text setting
    p1_win_text.setFont(gamefont);
    p1_win_text.setCharacterSize(80);



	p1_win_text.setFillColor(Color::Magenta);
	p1_win_text.setPosition(130, 450);
	p1_win_text.setString("Player 1 Wins");
	//Player2 Wins text setting
	p2_win_text.setFont(gamefont);
	p2_win_text.setCharacterSize(80);
	p2_win_text.setFillColor(Color(139, 69, 19));
	p2_win_text.setPosition(130, 450);
	p2_win_text.setString("Player 2 Wins");
	//Game Draw text setting
	Draw_text.setFont(gamefont);
	Draw_text.setCharacterSize(80);
	Draw_text.setFillColor(Color::White);
	Draw_text.setPosition(130, 450);
	Draw_text.setString("Game Draw");
	//Game over image setting
	go_texture.loadFromFile("assets/gameover.png");
	go_sprite.setTexture(go_texture);
	go_sprite.setScale(scaling_factor, scaling_factor);
	go_sprite.setPosition(160, 250);
	//Bird i win pic
	bird1_win_texture.loadFromFile("assets/bird1_win.png");
	bird1_win_sprite.setTexture(bird1_win_texture);
	bird1_win_sprite.setScale(2.0f, 2.0f);
	bird1_win_sprite.setPosition(250.f, 400.f);
	//Bird 2 win pic
	bird2_win_texture.loadFromFile("assets/bird2_win.png");
	bird2_win_sprite.setTexture(bird2_win_texture);
	bird2_win_sprite.setScale(2.0f, 2.0f);
	bird2_win_sprite.setPosition(250.f, 400.f);

	Pipe::loadTextures();
}
void Game::doProcessing(Time & dt)
{
    if (enter_pressed)
    {
    moveGround(dt);
    if (pipe_counter > pipe_spawn_time)
    {
    pipes.push_back(Pipe(dist(rd)));
    pipe_counter = 0;
    }
    pipe_counter++;
    for (int i = 0; i < pipes.size(); i++)
    {
    pipes[i].update(dt);
    if (pipes[i].getRightBound() < 0)
    {
    pipes.erase(pipes.begin() + i);
    }
    }
    checkCollisions1();
    checkCollisions2();
    checkScore();
}

}

bird1.update1(dt);
bird2.update2(dt);

void Game::startGameLoop()
{
    Clock clock;

    // Display the main menu screen
    showMainMenuScreen();
    //Game Loop
    while (win.isOpen())
    {
    Time dt = clock.restart();
    Event event;
    //Event Loop
    while (win.pollEvent(event))
    {
    if (event.type == Event::Closed)
    {
    win.close();
    }
    if (event.type == Event::KeyPressed && (run_game1 || run_game2))
    {
    if (event.key.code == Keyboard::Enter && lenter_pressed)
    {
    enter_pressed = true;
    bird1.bindshouldfly(true);
    bird2.bindshouldfly(true);
    }
    if (event.key.code == Keyboard::Space && enter_pressed)
    {
    bird1.bindflap(dt);
    }
    if (event.key.code == Keyboard::Up && enter_pressed)
    {
    bird2.bindflap(dt);
    }
    if (event.type == Event::KeyPressed && (|run_game1 || |run_game2))
    {
    if (event.key.code == Keyboard::R && (|run_game1 ||!run_game2))
    return raster(name);
    {
    restartGame();
    }
    }
    }
    if (enter_pressed)
    {
    doProcessing(dt);
    }
    }
    draw();

//display the window
    win.display();
}
}
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

void Game::showGameScreen()
{
    // Set the flag to start the game and hide the main menu and controls screens
    showMainMenu = false;
    showControls = false;
    restartGame();
}
void Game::checkCollisions1()
{
	if (pipes.size() > 0)
	{
		if
		(pipes[0].sprite_down.getGlobalBounds().intersects(bird1.bird1_sprite.getGlobalBounds()) ||
		pipes[0].sprite_up.getGlobalBounds().intersects(bird1.bird1_sprite.getGlobalBounds())
		||
		bird1.bird1_sprite.getGlobalBounds().top >= 540)
		{
			enter_pressed = false;
			run_game1 = false;
			bird1Collided = true;
		}
	}
}

void Game::checkCollisions2()
{
if (pipes.size() > 0)
{
if
(pipes[0].sprite_down.getGlobalBounds().intersects(bird2.bird2_sprite.getGlobalBounds()) ||
pipes[0].sprite_up.getGlobalBounds().intersects(bird2.bird2_sprite.getGlobalBounds())
||
bird2.bird2_sprite.getGlobalBounds().top >= 540)
{
enter_pressed = false;
run_game2 = false;
bird2Collided = true;
}
}
}


void Game::checkScore()
{
if (pipes.size() > 0)
{
if (!start_monitoring)
{
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
if (bird1.bird1_sprite.getGlobalBounds().left >
pipes[0].getRightBound())
{
score_p1++;
player1_score_text.setString("Player 1: " +
toString(score_p1));
start_monitoring = false;
}
if (bird2.bird2_sprite.getGlobalBounds().left >
pipes[0].getRightBound())
{
score_p2++;
player2_score_text.setString("Player 2: " +
toString(score_p2));
start_monitoring = false;
}
}
}
}


void Game::draw()
{
    win.draw(background_sprite);
    for (Pipe& pipe : pipes)
    {
    win.draw(pipe.sprite_down);
    win.draw(pipe.sprite_up);
    }
    win.draw(ground_sprite1);
    win.draw(ground_sprite2);

if (run_game1 && run_game2) //If no one collides draw both birds
{
    win.draw(bird1.bird1_sprite);
    win.draw(bird2.bird2_sprite);
}
else if (run_game1 && run_game2) //If bird1 collides bird2 disappears
{
    if (bird1Collided)
    {
    win.draw(bird1.bird1_sprite);
    win.draw(bird2_win_sprite);
    }
    else
    {
    win.draw(bird2.bird2_sprite);
    win.draw(bird1_win_sprite);
    }
}
else if (run_game1 && fun_game2) //If bird2 collides bird1 disappears
{
    if (bird2Collided)
    {
    win.draw(bird2.bird2_sprite);
    win.draw(bird1_win_sprite);
    }
    else
    {
    win.draw(bird1.bird1_sprite);
    win.draw(bird2_win_sprite);
    }
}
else if (run_game1 && fun_game2)
{
    if (bird1Collided && bird2Collided)
    {
    win.draw(bird1.bird1_sprite);
    }

win.draw(bird2.bird2_sprite);
}
else if (bird1Collided && lbird2Collided) // Bird 2 wins, bird 1 disappears
{
    win.draw(bird1.bird1_sprite);
}
else if (lbird1Collided && bird2Collided) // Bird 1 wins, bird 2 disappears
{
    win.draw(bird2.bird2_sprite);
}

win.draw(player1_score_text);
win.draw(player2_score_text);

if (!run_game1 && !run_game2)
{
    win.draw(go_sprite);
    win.draw(playagain_text);
    win.draw(Draw_text);
}
else if (!run_game1)
{
    win.draw(go_sprite);
    win.draw(playagain_text);
    win.draw(p2_win_text);
}
else if (!run_game2)
{
    win.draw(go_sprite);
    win.draw(playagain_text);
    win.draw(p1_win_text);
}

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


}
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

std::string Game::toString(int num)
{
    std::stringstream ss;
    ss << num;
    return ss.str();

}
}
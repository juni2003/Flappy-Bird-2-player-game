#pragma once
#include<SFML/Graphics.hpp>
#include"Bird.h"
#include<vector>
#include"Pipe.h"
#include<random>
using namespace sf;
class Game
{
private:
Texture menu_texture, controls_texture; //pics for loading screen
Sprite menu_sprite, controls_sprite;
Texture background, ground_texture; //background pics
Sprite background_sprite, ground_sprite1, ground_sprite2;
Bird bird1; //bird class's object
Bird bird2;
bool enter_pressed, run_game1, run_game2, start_monitoring;
bool bird1Collided;
bool bird2Collided;
bool showMainMenu;
bool showControls;
const int move_speed = 270; //moving speed
void draw(); //displays pics
void moveGround(Time&);
void doProcessing(Time& dt);
Texture bird1_win_texture;
Sprite bird1_win_sprite;
Texture bird2_win_texture;
Sprite bird2_win_sprite;
void showMainMenuScreen();
void showGameScreen();
void showControlsScreen();
void checkCollisions1();
void checkCollisions2();
void restartGame();
void checkScore();
std::string toString(int);
int pipe_counter, pipe_spawn_time, score_p1, score_p2;
std::vector<Pipe> pipes;
std::random_device rd; //for randomly chaning pipes position
std::uniform_int_distribution<int> dist{ 250,550 };
Font normalfont;
Font gamefont;
Text playagain_text, player1_score_text, player2_score_text;
Text p1_win_text, p2_win_text, Draw_text;
Texture go_texture;
Sprite go_sprite;
public:
Game(RenderWindow&);
RenderWindow& win;
void startGameLoop();
};

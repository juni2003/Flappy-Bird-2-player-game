#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
class Pipe
{
private:
static Texture pipe_down, pipe_up; //for loading pipes
static int pipe_distance; //distance between pipes
public:
Pipe(int);
Sprite sprite_up, sprite_down;
static void loadTextures();
void update(Time&);
float getRightBound();
static int move_speed;
};
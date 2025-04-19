#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
class Bird
{
private:
Texture bird1[2]; //for loading pics of bird
Texture bird2[2];
const int gravity; // for the falling of bird
const int birdflapspeed; //force of which bird flies up
float velocity;
int animation, animation_switch; //changes pictyre
bool birdfly; //check for bird flying
public:
Sprite bird1_sprite;
Sprite bird2_sprite;
Bird();
void birdshouldfly(bool); //function declaration
void birdflap(Time&);
void bird1_resetPosition();
void bird2_resetPosition();
void update1(Time&);
void update2(Time&);
float getRightBound();
};
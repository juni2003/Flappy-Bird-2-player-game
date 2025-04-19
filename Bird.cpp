#include "Bird.h"
#include"Globals.h"
using namespace sf;
Bird::Bird() :
gravity(14), //giving values
birdflapspeed(300),
animation(0),
animation_switch(0),
birdfly(false)
{
bird1[0].loadFromFile("assets/bird1down.png"); //loading actual
pics
bird1[1].loadFromFile("assets/bird1up.png");
bird2[0].loadFromFile("assets/bird2down.png");
bird2[1].loadFromFile("assets/bird2up.png");
bird1_sprite.setTexture(bird1[0]); //setting pics
bird1_sprite.setScale(scaling_factor, scaling_factor);
bird2_sprite.setTexture(bird2[0]);
bird2_sprite.setScale(scaling_factor, scaling_factor);
bird1_resetPosition(); //function call
bird2_resetPosition();
}
void Bird::update1(Time& dt)
{
if (bird1_sprite.getGlobalBounds().top < 548 && birdfly) //updating
the two pics of bird
{
if (animation == 5)
{
bird1_sprite.setTexture(bird1[animation_switch]);
if (animation_switch) animation_switch = 0;
else animation_switch = 1;
animation = 0;
}
animation++;
velocity += gravity * dt.asSeconds();
bird1_sprite.move(0, velocity);
if (bird1_sprite.getGlobalBounds().top < 0)
bird1_sprite.setPosition(100, 0);
}
}
void Bird::update2(Time& dt)
{
if (bird2_sprite.getGlobalBounds().top < 548 && birdfly)
{
if (animation == 5)
{
bird2_sprite.setTexture(bird2[animation_switch]);
if (animation_switch) animation_switch = 0;
else animation_switch = 1;
animation = 0;
}
animation++;
velocity += gravity * dt.asSeconds();
bird2_sprite.move(0, velocity);
if (bird2_sprite.getGlobalBounds().top < 0)
bird2_sprite.setPosition(100, 0);
}
}
void Bird::birdflap(Time& dt) //checking birdflap
{
velocity = -birdflapspeed * dt.asSeconds();
}
float Bird::getRightBound()
{
return bird1_sprite.getGlobalBounds().left +
bird1_sprite.getGlobalBounds().width;
}
void Bird::bird1_resetPosition()
{
bird1_sprite.setPosition(100, 50);
velocity = 0;
}
void Bird::bird2_resetPosition()
{
bird2_sprite.setPosition(100, 150);
velocity = 0;
}
void Bird::birdshouldfly(bool should_fly)
{
this->birdfly = should_fly;
}

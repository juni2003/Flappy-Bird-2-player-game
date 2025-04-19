#include "Pipe.h"
#include"Globals.h"
using namespace sf;
Texture Pipe::pipe_down, Pipe::pipe_up;
int Pipe::pipe_distance = 170, Pipe::move_speed = 400; //assigning values
Pipe::Pipe(int y_pos)
{
sprite_down.setTexture(pipe_down);
sprite_up.setTexture(pipe_up);
sprite_down.setScale(scaling_factor, scaling_factor);
sprite_up.setScale(scaling_factor, scaling_factor);
sprite_up.setPosition(window_width, y_pos);
sprite_down.setPosition(window_width, y_pos - pipe_distance -
sprite_up.getGlobalBounds().height);
}
void Pipe::update(sf::Time& dt)
{
sprite_up.move(-move_speed * dt.asSeconds(), 0.f);
sprite_down.move(-move_speed * dt.asSeconds(), 0.f);
}
void Pipe::loadTextures()
{
pipe_down.loadFromFile("assets/pipedown.png");
pipe_up.loadFromFile("assets/pipe.png");
}
float Pipe::getRightBound()
{
return sprite_down.getGlobalBounds().left +
sprite_down.getGlobalBounds().width;
}
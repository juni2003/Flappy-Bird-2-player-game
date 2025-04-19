#include<SFML/Graphics.hpp>
#include"Globals.h"
#include"Game.h"
using namespace sf;
int main()
{
RenderWindow win(VideoMode(window_width, window_height), "Flappy
Bird");
Game game(win);
game.startGameLoop();
return 0;
}

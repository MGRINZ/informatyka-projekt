#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Level.h"

using namespace std;
using namespace sf;

int main()
{
	Game::getInstance().init();
	Game::getInstance().run();
	return 0;
}
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace std;
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(Game::width, Game::height), "Gra");
	window.setFramerateLimit(60);

	Level level;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		level.draw(window);
		window.display();
	}
	return 0;
}
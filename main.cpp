#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Level.h"

using namespace std;
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(Game::WIDTH, Game::HEIGHT), "Gra");
	window.setFramerateLimit(60);
	
	Level level;
	level.load("level3.lvl");
	
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		
		window.clear();

		switch (level.getStatus())
		{
			case Level::LEVEL_STATUS_FINISHED:
			{
				break;
			}
			default:
			{
				level.handleEntities();
				level.handleItems();
				window.setView(level.getView());
			}
		}

		level.handleFinish();
		level.handleTimers();

		level.draw(window);

		window.display();
	}
	return 0;
}
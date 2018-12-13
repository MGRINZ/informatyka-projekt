#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Level.h"

#include "Button.h"	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

using namespace std;
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(Game::WIDTH, Game::HEIGHT), "Gra");
	window.setFramerateLimit(60);
	
	Level level;
	level.load("level3.lvl");

	Button btn(Vector2f(100, 50));
	btn.setPositiion(Vector2f(50, 50));

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
			case Level::Status::FINISHED:
			case Level::Status::FAILED:
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
		window.draw(btn);
		window.display();
	}
	return 0;
}
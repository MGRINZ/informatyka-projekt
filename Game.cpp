#include "Game.h"
#include <sstream>

Game& Game::getInstance()
{
	static Game instance;
	return instance;
}

void Game::init()
{
	window.create(VideoMode(Game::WIDTH, Game::HEIGHT), "Gra");
	window.setFramerateLimit(60);
	MAIN_FONT.loadFromFile("resources/fonts/verdana.ttf");
}

void Game::run()
{
	if (running)
		return;

	running = true;

	level.load("level3.lvl");

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		for (int i = 0; i < Button::buttons.size(); i++)
		{
			cout << (int)Button::buttons[i] << endl;
			Button::buttons[i]->handleEvents(window, &level.getView());
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
		window.display();
	}
}

Font& Game::getMainFont()
{
	return MAIN_FONT;
}

Level & Game::getLevel()
{
	return level;
}

string Game::getNextLevelFilename()
{
	string levelFilename = level.getLevelFilename();
	stringstream ss;
	ss << "level" << (atoi(levelFilename.substr(5, 1).c_str()) + 1) << ".lvl";
	return ss.str();
}

void Game::nextLevel()
{
	level.load(getNextLevelFilename());
}

Game::Game()
{
}
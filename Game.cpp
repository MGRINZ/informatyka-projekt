#include "Game.h"
#include <sstream>

Game& Game::getInstance()
{
	static Game instance;
	return instance;
}

void Game::init()
{
	status = Status::LOADING;
	window.create(VideoMode(Game::WIDTH, Game::HEIGHT), "Gra");
	window.setFramerateLimit(60);
	MAIN_FONT.loadFromFile("resources/fonts/verdana.ttf");
	menu = new GameMenu();
	status = Status::IN_MENU;
}

void Game::run()
{
	if (running)
		return;

	running = true;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		//Obs�uga zdarze� przycisk�w
		//zwyk�y for zamiast foreach �eby nie wywo�ywa� metod zniszczonych obiekt�w
		for (int i = 0; i < Button::buttons.size(); i++)
			Button::buttons[i]->handleEvents(window, &level.getView());

		window.clear();

		switch (status)
		{
			case LOADING:
				break;
			case IN_MENU:
			{
				menu->draw(window);
				break;
			}
			case IN_GAME:
			{
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
				break;
			}
			case EXIT:
			{
				window.close();
				break;
			}
		}

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

void Game::startLevel(int levelId)
{
	stringstream ss;
	ss << "level" << levelId << ".lvl";
	level.load(ss.str());
	status = Status::IN_GAME;
	menu->setStatus(menu->NONE);
}

void Game::backToMenu()
{
	menu->setStatus(menu->MAIN_MENU);
	status = Status::IN_MENU;
}

void Game::loadSave(Save save)
{
	this->save = save;
}

Save Game::getSave()
{
	return save;
}

void Game::exit()
{
	status = Status::EXIT;
}

Game::Game()
{
}
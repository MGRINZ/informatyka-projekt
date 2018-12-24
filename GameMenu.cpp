#include "GameMenu.h"
#include "Game.h"
#include "MainMenu.h"
#include "NewGameMenu.h"

GameMenu::GameMenu()
{
	bg.setTexture("resources/textures/gui/menu_bg.png");
	view = View(FloatRect(0, 0, Game::WIDTH, Game::HEIGHT));
	setStatus(Status::MAIN_MENU);
}

void GameMenu::draw(RenderWindow & window)
{
	window.setView(view);
	menu->setPosition(Vector2f(Game::WIDTH / 2, Game::HEIGHT / 2));

	window.draw(bg);
	window.draw(*menu);
}

void GameMenu::setStatus(Status status)
{
	this->status = status;
	if (menu != nullptr)
	{
		delete menu;
		menu = nullptr;
	}

	switch(status)
	{
		case GameMenu::MAIN_MENU:
		{
			menu = new MainMenu(*this);
			break;
		}
		case GameMenu::NEW_GAME_MENU:
		{
			menu = new NewGameMenu(*this);
			break;
		}
		case GameMenu::NEW_GAME_DIFFICULTY_MENU:
		{

			break;
		}
		case GameMenu::LOAD_MENU:
		{

			break;
		}
		case GameMenu::HELP_MENU:
		{

			break;
		}
	}	
}

#include "GameMenu.h"
#include "Game.h"
#include "MainMenu.h"
#include "NewGameMenu.h"
#include "NewGameDifficultyMenu.h"
#include "LoadMenu.h"
#include "LoadLevelMenu.h"
#include "HelpMenu.h"

GameMenu::GameMenu()
{
	difficultyNames[0] = "Ijzi";
	difficultyNames[1] = "Midjum";
	difficultyNames[2] = "Hard";

	bg.setTexture("resources/textures/gui/menu_bg.png");
	view = View(FloatRect(0, 0, Game::WIDTH, Game::HEIGHT));
	setStatus(Status::MAIN_MENU);
}

GameMenu::~GameMenu()
{
	if(menu != NULL)
		delete menu;
}

void GameMenu::draw(RenderWindow & window)
{
	window.setView(view);
	Game::getInstance().getLevel().setView(view);
	if(menu->getMenuId().empty())
		menu->setPosition(Vector2f(Game::WIDTH / 2, Game::HEIGHT / 2 - 50));

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
			Game::getInstance().getLevel().resetEndScreen();
			Game::getInstance().getLevel().resetPauseMenu();
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
			menu = new NewGameDifficultyMenu(*this);
			break;
		}
		case GameMenu::LOAD_MENU:
		{
			menu = new LoadMenu(*this);
			break;
		}
		case GameMenu::LOAD_LEVEL_MENU:
		{
			menu = new LoadLevelMenu(*this);
			break;
		}
		case GameMenu::HELP_MENU:
		{
			menu = new HelpMenu(*this);
			break;
		}
	}	
}

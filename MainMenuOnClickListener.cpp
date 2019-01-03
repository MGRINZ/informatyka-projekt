#include "MainMenuOnClickListener.h"
#include "Game.h"

MainMenuOnClickListener::MainMenuOnClickListener(GameMenu &gameMenu)
{
	this->gameMenu = &gameMenu;
}

void MainMenuOnClickListener::onClick(int index)
{
	switch(index)
	{
		case NEW_GAME:
		{
			gameMenu->setStatus(gameMenu->NEW_GAME_MENU);
			break;
		}
		case LOAD_GAME:
		{
			gameMenu->setStatus(gameMenu->LOAD_MENU);
			break;
		}
		case HELP:
		{
			gameMenu->setStatus(gameMenu->HELP_MENU);
			break;
		}
		case EXIT:
		{
			Game::getInstance().exit();
			break;
		}
		default:
			break;
	}
}

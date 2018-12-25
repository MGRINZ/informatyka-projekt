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
			break;
		}
		case HELP:
		{
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

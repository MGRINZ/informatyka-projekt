#include "MainMenuOnClickListener.h"
#include "Game.h"

MainMenuOnClickListener::MainMenuOnClickListener(GameMenu &menu)
{
	this->menu = &menu;
}

void MainMenuOnClickListener::onClick(int index)
{
	switch(index)
	{
		case NEW_GAME:
		{
			menu->setStatus(menu->NEW_GAME_MENU);
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

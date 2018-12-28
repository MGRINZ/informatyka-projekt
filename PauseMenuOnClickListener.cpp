#include "PauseMenuOnClickListener.h"
#include "Game.h"

PauseMenuOnClickListener::PauseMenuOnClickListener()
{
}

void PauseMenuOnClickListener::onClick(int index)
{
	switch (index)
	{
		case PauseMenuOnClickListener::CONTINUE:
		{
			Game::getInstance().getLevel().resetPauseMenu();
			Game::getInstance().getLevel().setStatus(Level::Status::IN_GAME);
			break;
		}
		case PauseMenuOnClickListener::RESTART:
		{
			Game::getInstance().getLevel().restart();
			break;
		}
		case PauseMenuOnClickListener::HELP:
		{
			Level &level = Game::getInstance().getLevel();
			level.resetPauseMenu();
			level.showHelpMenu();
			level.setStatus(Level::Status::HELP_MENU);
			break;
		}
		case PauseMenuOnClickListener::MAIN_MENU:
		{
			Game::getInstance().backToMenu();
			break;
		}
		default:
			break;
	}
}


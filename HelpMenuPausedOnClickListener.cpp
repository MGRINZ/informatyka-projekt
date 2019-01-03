#include "HelpMenuPausedOnClickListener.h"
#include "Game.h"



HelpMenuPausedOnClickListener::HelpMenuPausedOnClickListener()
{
}

void HelpMenuPausedOnClickListener::onClick(int index)
{
	if (index == Selection::BACK)
	{
		Level &level = Game::getInstance().getLevel();
		level.showPauseMenu();
		level.resetHelpMenu();
		level.setStatus(Level::Status::PAUSED);
	}
}


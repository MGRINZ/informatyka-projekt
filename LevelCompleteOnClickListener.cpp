#include "LevelCompleteOnClickListener.h"
#include "Game.h"



LevelCompleteOnClickListener::LevelCompleteOnClickListener()
{
}

void LevelCompleteOnClickListener::onClick(int index)
{
	switch (index)
	{
		case MAIN_MENU:
			break;
		case RESTART:
		{
			Game::getInstance().getLevel().restart();
			break;
		}
		case NEXT_LEVEL:
		{
			Game::getInstance().nextLevel();
			break;
		}
	}
}
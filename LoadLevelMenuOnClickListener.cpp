#include "LoadLevelMenuOnClickListener.h"
#include "utils.h"
#include "Game.h"
#include "Save.h"
#include <sstream>

LoadLevelMenuOnClickListener::LoadLevelMenuOnClickListener(GameMenu &gameMenu)
{
	this->gameMenu = &gameMenu;
}

void LoadLevelMenuOnClickListener::onClick(int index)
{
	int i;
	for (i = 0; i < 5; i++)
	{
		stringstream levelPath;
		levelPath << "resources/levels/level" << i + 1 << ".lvl";
		if (!Utils::fexists(levelPath.str()))
			break;
	}

	if (index < i)
		Game::getInstance().startLevel(index + 1);
	else
		gameMenu->setStatus(gameMenu->LOAD_MENU);
}


#include "NewGameMenuOnClickListener.h"
#include "Game.h"
#include "Save.h"

NewGameMenuOnClickListener::NewGameMenuOnClickListener(GameMenu &gameMenu)
{
	this->gameMenu = &gameMenu;
}

void NewGameMenuOnClickListener::onClick(int index)
{
	switch (index)
	{
		case 0:
		case 1:
		case 2:
		{
			gameMenu->setStatus(gameMenu->NEW_GAME_DIFFICULTY_MENU);
			Save save;
			save.setSlot(index);
			Game::getInstance().loadSave(save);
			break;
		}
		case BACK:
		{
			gameMenu->setStatus(gameMenu->MAIN_MENU);
			break;
		}
	}
}

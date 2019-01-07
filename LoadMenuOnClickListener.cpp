#include "LoadMenuOnClickListener.h"
#include "Save.h"
#include "Game.h"

LoadMenuOnClickListener::LoadMenuOnClickListener(GameMenu &gameMenu) : NewGameMenuOnClickListener(gameMenu) {}

void LoadMenuOnClickListener::onClick(int index)
{
	switch (index)
	{
		case 0:
		case 1:
		case 2:
		{
			Save save;
			save.setSlot(index);
			save.read();
			Game::getInstance().loadSave(save);
			gameMenu->setStatus(gameMenu->LOAD_LEVEL_MENU);
			break;
		}
		case BACK:
		{
			gameMenu->setStatus(gameMenu->MAIN_MENU);
			break;
		}
	}
}

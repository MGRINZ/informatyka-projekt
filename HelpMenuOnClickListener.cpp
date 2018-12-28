#include "HelpMenuOnClickListener.h"

HelpMenuOnClickListener::HelpMenuOnClickListener(GameMenu &gameMenu)
{
	this->gameMenu = &gameMenu;
}

void HelpMenuOnClickListener::onClick(int index)
{
	if(index == Selection::BACK)
		gameMenu->setStatus(gameMenu->MAIN_MENU);
}

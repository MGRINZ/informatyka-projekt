#include "NewGameMenuOnClickListener.h"
#include <iostream>

NewGameMenuOnClickListener::NewGameMenuOnClickListener(GameMenu &menu)
{
	this->menu = &menu;
}

void NewGameMenuOnClickListener::onClick(int index)
{
	switch (index)
	{
		case 0:
		case 1:
		case 2:
		{

			break;
		}
		case BACK:
		{
			menu->setStatus(menu->MAIN_MENU);
			break;
		}
	}
}

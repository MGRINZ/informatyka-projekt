#pragma once
#include "ButtonsGroupOnClickListener.h"
#include "GameMenu.h"

class MainMenuOnClickListener : public ButtonsGroupOnClickListener
{
private:
	GameMenu *menu;
	enum Selection
	{
		NEW_GAME,
		LOAD_GAME,
		HELP,
		EXIT
	};
public:
	MainMenuOnClickListener(GameMenu &menu);
	void onClick(int index);
};


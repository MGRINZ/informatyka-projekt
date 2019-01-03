#pragma once
#include "ButtonsGroupOnClickListener.h"
#include "GameMenu.h"

class MainMenuOnClickListener : public ButtonsGroupOnClickListener
{
private:
	GameMenu *gameMenu;
	enum Selection
	{
		NEW_GAME,
		LOAD_GAME,
		HELP,
		EXIT
	};
public:
	MainMenuOnClickListener(GameMenu &gameMenu);
	void onClick(int index);
};


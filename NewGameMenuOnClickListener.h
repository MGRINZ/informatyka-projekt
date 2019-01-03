#pragma once
#include "ButtonsGroupOnClickListener.h"
#include "GameMenu.h"

class NewGameMenuOnClickListener : public ButtonsGroupOnClickListener
{
protected:
	GameMenu *gameMenu;
	enum Selection
	{
		BACK = 3
	};
public:
	NewGameMenuOnClickListener(GameMenu &gameMenu);
	void onClick(int index);
};


#pragma once
#include "ButtonsGroupOnClickListener.h"
#include "GameMenu.h"

class NewGameMenuOnClickListener : public ButtonsGroupOnClickListener
{
private:
	GameMenu *menu;
	enum Selection
	{
		BACK = 3
	};
public:
	NewGameMenuOnClickListener(GameMenu &menu);
	void onClick(int index);
};


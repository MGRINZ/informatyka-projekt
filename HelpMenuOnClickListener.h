#pragma once
#include "ButtonsGroupOnClickListener.h"
#include "GameMenu.h"

class HelpMenuOnClickListener : public ButtonsGroupOnClickListener
{
private:
	GameMenu *gameMenu;
	enum Selection
	{
		BACK
	};
public:
	HelpMenuOnClickListener(GameMenu &gameMenu);
	void onClick(int index);
};


#pragma once
#include "ButtonsGroupOnClickListener.h"
#include "GameMenu.h"

class NewGameDifficultyMenuOnClickListener : public ButtonsGroupOnClickListener
{
private:
	GameMenu *gameMenu;
	enum Selection
	{
		EASY,
		NORMAL,
		HARD,
		BACK
	};
public:
	NewGameDifficultyMenuOnClickListener(GameMenu &gameMenu);
	void onClick(int index);
};


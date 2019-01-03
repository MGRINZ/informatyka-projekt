#pragma once
#include "ButtonsGroupOnClickListener.h"
#include "GameMenu.h"

class LoadLevelMenuOnClickListener : public ButtonsGroupOnClickListener
{
private:
	GameMenu *gameMenu;
public:
	LoadLevelMenuOnClickListener(GameMenu &gameMenu);
	void onClick(int index);
};


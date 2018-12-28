#pragma once
#include "ButtonsGroupOnClickListener.h"
#include "Level.h"

class PauseMenuOnClickListener : public ButtonsGroupOnClickListener
{
private:
	enum Selection
	{
		CONTINUE,
		RESTART,
		HELP,
		MAIN_MENU
	};
public:
	PauseMenuOnClickListener();
	void onClick(int index);
};


#pragma once
#include "ButtonsGroupOnClickListener.h"

class LevelFailedOnClickListener : public ButtonsGroupOnClickListener
{
private:
	enum Selection
	{
		MAIN_MENU,
		RESTART
	};
public:
	LevelFailedOnClickListener();
	void onClick(int index);
};


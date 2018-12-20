#pragma once
#include "ButtonsGroupOnClickListener.h"

class LevelCompleteOnClickListener : public ButtonsGroupOnClickListener
{
private:
	enum Selection
	{
		MAIN_MENU,
		RESTART,
		NEXT_LEVEL
	};
public:
	LevelCompleteOnClickListener();
	void onClick(int index);
};


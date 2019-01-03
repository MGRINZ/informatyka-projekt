#pragma once
#include "ButtonsGroupOnClickListener.h"

class HelpMenuPausedOnClickListener : public ButtonsGroupOnClickListener
{
private:
	enum Selection
	{
		BACK
	};
public:
	HelpMenuPausedOnClickListener();
	void onClick(int index);
};


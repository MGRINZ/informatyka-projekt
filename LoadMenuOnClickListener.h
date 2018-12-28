#pragma once
#include "NewGameMenuOnClickListener.h"

class LoadMenuOnClickListener : public NewGameMenuOnClickListener
{
public:
	LoadMenuOnClickListener(GameMenu &gameMenu);
	void onClick(int index);
};


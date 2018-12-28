#pragma once
#include "LevelEndScreen.h"
#include "PauseMenuOnClickListener.h"

class PauseMenu : public LevelEndScreen
{
private:
	PauseMenuOnClickListener onClickListener;
public:
	PauseMenu();
};
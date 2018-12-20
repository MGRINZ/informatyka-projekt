#pragma once
#include "LevelEndScreen.h"
#include "LevelFailedOnClickListener.h"

class LevelFailedScreen : public LevelEndScreen
{
private:
	LevelFailedOnClickListener onClickListener;
public:
	LevelFailedScreen(Vector2f position);
};


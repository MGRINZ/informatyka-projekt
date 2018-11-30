#pragma once
#include "LevelEndScreen.h"
#include "HUD.h"

class LevelCompleteScreen :	public LevelEndScreen
{
private:
	HealthBar healthBar;
	ItemsBar itemBar;
	EnemiesBar enemiesBar;
	TimeBar timeBar;

public:
	LevelCompleteScreen(HUD * hud);

};


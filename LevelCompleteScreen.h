#pragma once
#include "LevelEndScreen.h"
#include "HUD.h"

class LevelCompleteScreen :	public LevelEndScreen
{
private:
	HUD *hud;
	View *view;
	HealthBar healthBar;
	ItemsBar itemBar;
	EnemiesBar enemiesBar;
	TimeBar timeBar;

public:
	LevelCompleteScreen(HUD * hud, View * view);
	void draw(RenderWindow &window);
};


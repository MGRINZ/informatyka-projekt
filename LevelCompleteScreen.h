#pragma once
#include "LevelEndScreen.h"
#include "HUD.h"
#include "Counter.h"

class LevelCompleteScreen :	public LevelEndScreen
{
private:
	const int ANIMATION_TIME_CONSTANT = 500;
	HUD *hud;
	View *view;
	HealthBar healthBar;
	ItemsBar itemsBar;
	EnemiesBar enemiesBar;
	TimeBar timeBar;
	Clock *animationClock;
	Sprite arrows[4];
	Counter counters[4];
	void showUpHealtBar();
	void showUpItemsBar();
	void showUpEnemiesBar();
	void showUpTimeBar();

public:
	LevelCompleteScreen(HUD * hud);
	void draw(RenderWindow &window);
};


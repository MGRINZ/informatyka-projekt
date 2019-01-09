#pragma once
#include "LevelEndScreen.h"
#include "LevelCompleteOnClickListener.h"
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
	Font font;
	Text scoreText;
	Clock *animationClock;
	Counter counters[5];
	void showUpHealtBar();
	void showUpItemsBar();
	void showUpEnemiesBar();
	void hudBarCounting(HUDBar & sourceHUDBar, HUDBar & targetHUDBar, int elapsedTime, int counterIndex, int score, int bonusScore);
	void showUpTimeBar();
	void showUpScore();
	LevelCompleteOnClickListener onClickListener;

public:
	LevelCompleteScreen(HUD * hud, Vector2f position);
	~LevelCompleteScreen();
	void draw(RenderWindow &window);
};


#include "LevelCompleteScreen.h"

LevelCompleteScreen::LevelCompleteScreen(HUD * hud)
{
	setHeader("Poziom ukonczony");
	healthBar = *hud->getHealthBar();
	itemBar = *hud->getItemsBar();
	enemiesBar = *hud->getEnemiesBar();
	timeBar = *hud->getTimeBar();

	//healthBar.setPosition();
}

void LevelCompleteScreen::draw(RenderWindow & window)
{
	LevelEndScreen::draw(window);
	healthBar.draw(window);
}

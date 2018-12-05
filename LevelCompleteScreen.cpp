#include "LevelCompleteScreen.h"
#include <iostream>

using namespace std;

LevelCompleteScreen::LevelCompleteScreen(HUD * hud, View * view)
{
	setHeader("Poziom ukonczony");
	this->hud = hud;
	this->view = view;
}

void LevelCompleteScreen::draw(RenderWindow & window)
{
	LevelEndScreen::draw(window);

	healthBar = *hud->getHealthBar();
	itemBar = *hud->getItemsBar();
	enemiesBar = *hud->getEnemiesBar();
	timeBar = *hud->getTimeBar();

	Vector2f vc = view->getCenter();
	Vector2f vs = view->getSize();
	Vector2f refP(vc.x - vs.x / 2, vc.y - vs.y / 2);

	healthBar.setPosition(Vector2f(refP.x + 100, refP.y + 300));

	healthBar.draw(window);
	itemBar.draw(window);
	enemiesBar.draw(window);
	timeBar.draw(window);
}

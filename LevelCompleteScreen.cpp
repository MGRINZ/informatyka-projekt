#include "LevelCompleteScreen.h"
#include "Game.h"
#include "utils.h"
#include <iostream>

using namespace std;

void LevelCompleteScreen::showUpHealtBar()
{
	if (!frame.isShownUp())
		return;

	bool fadedIn = false;

	fadedIn = healthBar.fadeIn(ANIMATION_TIME_CONSTANT);
	fadedIn = Utils::fadeIn(counters[0], ANIMATION_TIME_CONSTANT);

	if(!fadedIn)
		return;

	int elapsedTime = animationClock->getElapsedTime().asMilliseconds();
	int health = hud->getHealthBar()->getHealth();

	for (int i = 1; i <= health; i++)
		if (elapsedTime >= ANIMATION_TIME_CONSTANT + i * ANIMATION_TIME_CONSTANT && elapsedTime < ANIMATION_TIME_CONSTANT + i * ANIMATION_TIME_CONSTANT * 2)
				healthBar.setHealth(i);

	if (elapsedTime >= ANIMATION_TIME_CONSTANT * 2 && elapsedTime < ANIMATION_TIME_CONSTANT * (health + 3))
	{
		counters[0].set(health * Game::HEALTH_SCORE);
		counters[0].count(ANIMATION_TIME_CONSTANT * health);
	}
	else if (elapsedTime >= ANIMATION_TIME_CONSTANT * (health + 3))
	{
		if (health == healthBar.getMaxHealth())
			counters[0].set(health * Game::HEALTH_SCORE + Game::HEALTH_SCORE_BONUS, health * Game::HEALTH_SCORE);
		counters[0].count(ANIMATION_TIME_CONSTANT);
	}
}

void LevelCompleteScreen::showUpItemsBar()
{
	if (!frame.isShownUp())
		return;

	int elapsedTime = animationClock->getElapsedTime().asMilliseconds();

	if (elapsedTime < ANIMATION_TIME_CONSTANT * 0.5)
		return;

	bool fadedIn = false;

	fadedIn = itemsBar.fadeIn(ANIMATION_TIME_CONSTANT);
	fadedIn = Utils::fadeIn(counters[1], ANIMATION_TIME_CONSTANT);

	if (!fadedIn)
		return;

	elapsedTime -= ANIMATION_TIME_CONSTANT * 0.5;

	int items = hud->getItemsBar()->getCurrentItems();
	int maxItems = hud->getItemsBar()->getMaxItems();

	if (elapsedTime >= ANIMATION_TIME_CONSTANT && elapsedTime < ANIMATION_TIME_CONSTANT * 2)
		itemsBar.HUDBar::setItems((double) items / (ANIMATION_TIME_CONSTANT) * (elapsedTime - ANIMATION_TIME_CONSTANT), maxItems);
	else
		itemsBar.HUDBar::setItems(items, maxItems);

	if (elapsedTime >= ANIMATION_TIME_CONSTANT && elapsedTime < ANIMATION_TIME_CONSTANT * 3)
	{
		counters[1].set(items * Game::ITEMS_SCORE);
		counters[1].count(ANIMATION_TIME_CONSTANT);
	}
	else if (elapsedTime >= ANIMATION_TIME_CONSTANT * 3)
	{
		if (items == maxItems)
			counters[1].set(items * Game::ITEMS_SCORE + Game::ITEMS_SCORE_BONUS, items * Game::ITEMS_SCORE);
		counters[1].count(ANIMATION_TIME_CONSTANT);
	}
}

void LevelCompleteScreen::showUpEnemiesBar()
{
	if (!frame.isShownUp())
		return;

	int elapsedTime = animationClock->getElapsedTime().asMilliseconds();

	if (elapsedTime < ANIMATION_TIME_CONSTANT)
		return;

	bool fadedIn = false;

	fadedIn = enemiesBar.fadeIn(ANIMATION_TIME_CONSTANT);
	fadedIn = Utils::fadeIn(counters[2], ANIMATION_TIME_CONSTANT);

	if (!fadedIn)
		return;

	elapsedTime -= ANIMATION_TIME_CONSTANT;
}

void LevelCompleteScreen::showUpTimeBar()
{
	if (!frame.isShownUp())
		return;

	int elapsedTime = animationClock->getElapsedTime().asMilliseconds();

	if (elapsedTime < ANIMATION_TIME_CONSTANT * 1.5)
		return;

	bool fadedIn = false;

	fadedIn = timeBar.fadeIn(ANIMATION_TIME_CONSTANT);
	fadedIn = Utils::fadeIn(counters[3], ANIMATION_TIME_CONSTANT);

	if (!fadedIn)
		return;

	elapsedTime -= ANIMATION_TIME_CONSTANT * 1.5;
}

LevelCompleteScreen::LevelCompleteScreen(HUD * hud)
{
	setSize(Vector2f(Game::WIDTH * 0.8, Game::HEIGHT * 0.7));
	setHeader("Poziom ukonczony");
	this->hud = hud;
	
	healthBar.setMaxHealth(hud->getHealthBar()->getMaxHealth());
	healthBar.setHealth(0);
	healthBar.setPosition(Vector2f(50, 60));
	healthBar.hide();

	itemsBar.HUDBar::setItems(0, hud->getItemsBar()->getMaxItems());
	itemsBar.setPosition(Vector2f(50, 120));
	itemsBar.hide();

	enemiesBar.setPosition(Vector2f(50, 180));
	enemiesBar.hide();
	
	timeBar.setPosition(Vector2f(50, 240));
	timeBar.hide();

	container.append(healthBar);
	container.append(itemsBar);
	container.append(enemiesBar);
	container.append(timeBar);

	for (int i = 0; i < 4; i++)
	{
		counters[i].setPosition(Vector2f(400, 60 + i * 60));
		Color color = counters[i].getFillColor();
		Color outlineColor = counters[i].getOutlineColor();

		color.a = 0;
		outlineColor.a = 0;

		counters[i].setFillColor(color);
		counters[i].setOutlineColor(outlineColor);

		container.append(counters[i]);
	}
}

void LevelCompleteScreen::draw(RenderWindow & window)
{
	if (frame.isShownUp())
		if (animationClock == NULL)
			animationClock = new Clock();

	showUpHealtBar();
	showUpItemsBar();
	showUpEnemiesBar();
	showUpTimeBar();

	enemiesBar.HUDBar::setItems(hud->getEnemiesBar()->getCurrentItems(), hud->getEnemiesBar()->getMaxItems());
	timeBar.setTimeLeft(hud->getTimeBar()->getTimeLeft());

	LevelEndScreen::draw(window);
}

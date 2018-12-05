#pragma once

#include "HealthBar.h"
#include "ItemsBar.h"
#include "EnemiesBar.h"
#include "TimeBar.h"

class HUD
{
private:
	Vector2f position;
	HealthBar healthBar;
	ItemsBar itemsBar;
	EnemiesBar enemiesBar;
	TimeBar timeBar;
public:
	HUD();
	void draw(RenderWindow &window);
	void setPosition(Vector2f position);
	Vector2f getPosition();
	void move(Vector2f position);
	HealthBar* getHealthBar();
	ItemsBar* getItemsBar();
	EnemiesBar* getEnemiesBar();
	TimeBar* getTimeBar();
};
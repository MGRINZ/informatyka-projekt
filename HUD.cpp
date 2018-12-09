#include "HUD.h"

HUD::HUD()
{
	setPosition(Vector2f(50, 20));
}

void HUD::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(healthBar);
	target.draw(itemsBar);
	target.draw(enemiesBar);
	target.draw(timeBar);
}

void HUD::setPosition(Vector2f position)
{
	this->position = position;
	healthBar.setPosition(Vector2f(position));
	itemsBar.setPosition(Vector2f(position.x + 200, position.y));
	enemiesBar.setPosition(Vector2f(position.x + 350, position.y));
	timeBar.setPosition(Vector2f(position.x + 500, position.y));
}

Vector2f HUD::getPosition()
{
	return position;
}

void HUD::move(Vector2f position)
{
	healthBar.move(position);
	itemsBar.move(position);
	enemiesBar.move(position);
	timeBar.move(position);
}

HealthBar * HUD::getHealthBar()
{
	return &healthBar;
}

ItemsBar * HUD::getItemsBar()
{
	return &itemsBar;
}

EnemiesBar * HUD::getEnemiesBar()
{
	return &enemiesBar;
}

TimeBar * HUD::getTimeBar()
{
	return &timeBar;
}
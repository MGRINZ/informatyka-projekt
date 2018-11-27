#include "HealthBar.h"

HealthBar::HealthBar()
{
	healthTexture.loadFromFile("resources/textures/hud/health.png");
	healthTextureEmpty.loadFromFile("resources/textures/hud/health_empty.png");
	setHealth(3);
}

void HealthBar::draw(RenderWindow & window)
{
	for (int i = 0; i < maxHealth; i++)
		window.draw(health[i]);
}

void HealthBar::setHealth(int hp)
{
	for (int i = 0; i < maxHealth; i++)
	{
		if (i < hp)
			health[i].setTexture(healthTexture);
		else
			health[i].setTexture(healthTextureEmpty);
	}
}

void HealthBar::setMaxHealth(int maxHealth)
{
	this->maxHealth = maxHealth;
}

void HealthBar::setPosition(Vector2f position)
{
	this->position = position;
	for (int i = 0; i < maxHealth; i++)
		health[i].setPosition(Vector2f(position.x + i * 50, position.y));
}

void HealthBar::move(Vector2f position)
{
	this->position.x += position.x;
	this->position.y += position.y;
	for (int i = 0; i < maxHealth; i++)
		health[i].move(position);
}

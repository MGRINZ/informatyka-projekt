#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class HealthBar
{
private:
	Texture healthTexture;
	Texture healthTextureEmpty;
	Sprite health[3];
	int maxHealth = 3;
	Vector2f position;
public:
	HealthBar();
	void draw(RenderWindow &window);
	void setHealth(int hp);
	void setMaxHealth(int maxHealth);
	void setPosition(Vector2f position);
	void move(Vector2f position);
};


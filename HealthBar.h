#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class HealthBar : public Drawable
{
private:
	Texture healthTexture;
	Texture healthTextureEmpty;
	Sprite health[3];
	int maxHealth = 3;
	Vector2f position;
public:
	HealthBar();
	void draw(RenderTarget& target, RenderStates states) const override;
	void setHealth(int hp);
	int getHealth();
	void setMaxHealth(int maxHealth);
	int getMaxHealth();
	void setPosition(Vector2f position);
	void move(Vector2f position);
	bool fadeIn(int duration);
	void hide();
};


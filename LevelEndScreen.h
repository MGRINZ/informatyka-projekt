#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class LevelEndScreen
{
private:
	Vector2f position;
	RectangleShape overlay;
	RectangleShape container;
	Font headerFont;
	Text header;
public:
	LevelEndScreen();
	void draw(RenderWindow &window);
	void setPosition(Vector2f position);
};
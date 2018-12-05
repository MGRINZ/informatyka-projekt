#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Frame
{
private:
	Vector2f position;
	RectangleShape corners[4];
	RectangleShape edges[4];
	Texture cornersTextures[4];
	Texture edgesTextures[4];
	Clock animationClock;
public:
	Frame();
	//void showIn();
	void draw(RenderWindow &window);
	void setPosition(Vector2f position);
	Vector2f getPosition();
};


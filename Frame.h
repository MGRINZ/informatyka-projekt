#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Frame
{
private:
	Vector2f position;
	Vector2f size;
	Sprite corners[4];
	Sprite edges[4];
	Sprite container;
	Texture cornersTextures[4];
	Texture edgesTextures[4];
	Clock *animationClock;
	bool shownUp = false;
	void showUp();
public:
	Frame();
	void draw(RenderWindow &window);
	void setPosition(Vector2f position);
	Vector2f getPosition();
	void setSize(Vector2f size);
	Vector2f getSize(Vector2f size);
	Sprite* getContainer();
};


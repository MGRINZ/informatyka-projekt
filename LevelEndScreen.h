#pragma once
#include <SFML/Graphics.hpp>
#include "Frame.h"
#include "Container.h"
#include "ButtonsGroup.h"

using namespace std;
using namespace sf;

class LevelEndScreen
{
private:
	Vector2f position;
	Vector2f size;
	RectangleShape overlay;
	Font headerFont;
	Text header;
protected:
	Container container;
	Frame frame;
	ButtonsGroup menu;
public:
	LevelEndScreen();
	virtual void draw(RenderWindow &window);
	void setPosition(Vector2f position);
	void setHeader(string header);
	void setSize(Vector2f size);
	Vector2f getPosition();
};
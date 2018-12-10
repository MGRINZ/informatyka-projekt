#pragma once
#include <SFML/Graphics.hpp>
#include "Frame.h"
#include "Container.h"

using namespace std;
using namespace sf;

class LevelEndScreen
{
private:
	Vector2f position;
	RectangleShape overlay;
	Font headerFont;
	Text header;
protected:
	Container container;
	Frame frame;
public:
	LevelEndScreen();
	virtual void draw(RenderWindow &window);
	void setPosition(Vector2f position);
	void setHeader(string header);
	void setSize(Vector2f size);
};
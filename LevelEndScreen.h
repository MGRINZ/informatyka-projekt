#pragma once
#include <SFML/Graphics.hpp>
#include "Frame.h"

using namespace std;
using namespace sf;

class LevelEndScreen
{
private:
	Vector2f position;
	RectangleShape overlay;
	Frame frame;
	//RectangleShape container;
	RenderTexture container;
	Font headerFont;
	Text header;
public:
	LevelEndScreen();
	virtual void draw(RenderWindow &window);
	void setPosition(Vector2f position);
	void setHeader(string header);
};
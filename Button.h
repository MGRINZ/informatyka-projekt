#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "ButtonOnClickListener.h"

using namespace std;
using namespace sf;

class Button : public Drawable
{
private:
	Texture normalTexture;
	Texture hoverTexture;
	Texture pushedTexture;
	Sprite corners[4];
	Sprite edges[4];
	Sprite filling;
	vector<Sprite> edgesGroups[4];
	vector<Sprite> fillingGroup;
	IntRect edgesTextureRects[4];
	IntRect fillingTextureRect;
	Font font;
	Text text;
	Vector2f size;
	Vector2f position;
	Vector2f origin;
	int state = -1;
	enum State
	{
		NONE,
		MOUSE_OVER,
		MOUSE_DOWN,
		MOUSE_UP,
	};
	void setState(State state);
	ButtonOnClickListener *onClickListener;
public:
	static vector<Button*> buttons;
	Button(Vector2f size);
	Button(Vector2f size, string text);
	void draw(RenderTarget& target, RenderStates states) const;
	void setSize(Vector2f size);
	Vector2f getSize();
	void setPositiion(Vector2f position);
	Vector2f getPositiion();
	void setOrigin(Vector2f origin);
	void setText(string text);
	void handleEvents(Window &window, View *view);
	void setOnClickListener(ButtonOnClickListener &onClickListener);
};


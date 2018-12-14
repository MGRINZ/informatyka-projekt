#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Button : public Drawable
{
private:
	Texture normalTexture;
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
public:
	Button(Vector2f size);
	Button(Vector2f size, string text);
	void draw(RenderTarget& target, RenderStates states) const;
	void setSize(Vector2f size);
	void setPositiion(Vector2f position);
	void setOrigin(Vector2f origin);
	void setText(string text);
};


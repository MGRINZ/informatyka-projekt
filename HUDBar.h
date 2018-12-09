#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Item.h"

using namespace std;
using namespace sf;

class HUDBar : public Drawable
{
protected:
	Texture iconTexture;
	Sprite icon;
	Font counterFont;
	Text counter;
	vector<Item>* items;
	Vector2f position;
public:
	HUDBar();
	void draw(RenderTarget& target, RenderStates states) const override;
	void setPosition(Vector2f position);
	void move(Vector2f position);
};
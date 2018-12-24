#pragma once
#include "ButtonsGroup.h"

class Menu : public Drawable
{
private:
	Vector2f position;
protected:
	ButtonsGroup menu;
public:
	Menu();
	void draw(RenderTarget& target, RenderStates states) const;
	void setPosition(Vector2f position);
};


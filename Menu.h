#pragma once
#include "ButtonsGroup.h"
#include "ButtonsGroupOnClickListener.h"

class Menu : public Drawable
{
private:
	Vector2f position;
protected:
	string menuId;
	ButtonsGroup menu;
	ButtonsGroupOnClickListener *onClickListener;
public:
	Menu();
	~Menu();
	void draw(RenderTarget& target, RenderStates states) const;
	void setPosition(Vector2f position);
	string getMenuId();
};


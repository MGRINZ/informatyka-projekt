#pragma once
#include "Menu.h"
#include "Frame.h"
#include "Container.h"
#include "GameMenu.h"

class HelpMenu : public Menu
{
private:
	Vector2f position;
	Frame frame;
	Container container;
	Text headers[2];
	Text paragraphs[3];
public:
	HelpMenu();
	HelpMenu(GameMenu &gameMenu);
	void draw(RenderTarget& target, RenderStates states) const;
	void setPosition(Vector2f position);
};


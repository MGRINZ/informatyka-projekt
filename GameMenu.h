#pragma once
#include <SFML/Graphics.hpp>
#include "Background.h"
#include "Menu.h"
#include "MainMenu.h"

using namespace sf;

class GameMenu
{
private:
	View view;
	Background bg;
	Menu *menu;
public:
	GameMenu();
	void draw(RenderWindow &window);
};


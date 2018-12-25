#pragma once
#include <SFML/Graphics.hpp>
#include "Background.h"
#include "Menu.h"

using namespace sf;

class GameMenu
{
private:
	View view;
	Background bg;
	Menu *menu;
	int status;
public:
	enum Status
	{
		NONE,
		MAIN_MENU,
		NEW_GAME_MENU,
		NEW_GAME_DIFFICULTY_MENU,
		LOAD_MENU,
		HELP_MENU
	};
	GameMenu();
	void draw(RenderWindow &window);
	void setStatus(Status status);
};


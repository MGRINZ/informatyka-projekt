#include "GameMenu.h"
#include "Game.h"

GameMenu::GameMenu()
{
	bg.setTexture("resources/textures/gui/menu_bg.png");
	menu = new MainMenu();
	view = View(FloatRect(0, 0, Game::WIDTH, Game::HEIGHT));
}

void GameMenu::draw(RenderWindow & window)
{
	window.setView(view);
	menu->setPosition(Vector2f(Game::WIDTH / 2, Game::HEIGHT / 2));

	window.draw(bg);
	window.draw(*menu);
}

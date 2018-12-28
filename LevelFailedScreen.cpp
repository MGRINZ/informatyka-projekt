#include "LevelFailedScreen.h"
#include "Game.h"
#include "HealthBar.h"

LevelFailedScreen::LevelFailedScreen(Vector2f position)
{
	setSize(Vector2f(Game::WIDTH * 0.8, Game::HEIGHT * 0.3));
	setPosition(position);
	setHeader("Poziom nieukonczony");
	
	Button mainMenuButton(Vector2f(100, 50), "Menu");
	Button restartButton(Vector2f(100, 50), "Restart");

	menu.add(mainMenuButton);
	menu.add(restartButton);

	Vector2f mp = menu.getSize();
	menu.setOrigin(Vector2f(mp.x / 2, mp.y / 2));

	menu.setOnClickListener(onClickListener);
}

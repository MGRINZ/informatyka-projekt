#include "LevelFailedScreen.h"
#include "Game.h"
#include "HealthBar.h"

LevelFailedScreen::LevelFailedScreen()
{
	setSize(Vector2f(Game::WIDTH * 0.8, Game::HEIGHT * 0.3));
	setHeader("Poziom nieukonczony");

	HealthBar *hp = new HealthBar();
	container.append(*hp);
}

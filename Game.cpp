#include "Game.h"

Game& Game::getInstance()
{
	static Game instance;
	return instance;
}

void Game::init()
{
	MAIN_FONT.loadFromFile("resources/fonts/verdana.ttf");
}

Font& Game::getMainFont()
{
	return MAIN_FONT;
}

Game::Game()
{
}
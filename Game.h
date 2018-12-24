#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameMenu.h"
#include "Level.h"

using namespace sf;

class Game
{
private:
	Game();
	RenderWindow window;
	Font MAIN_FONT;
	bool running = false;
	GameMenu *menu;
	Level level;
	enum Status
	{
		LOADING,
		IN_MENU,
		IN_GAME
	};
	Status status;
public:
	static const int WIDTH = 800;
	static const int HEIGHT = 600;
	static const int HEALTH_SCORE = 1000;
	static const int ITEMS_SCORE = 500;
	static const int ENEMIES_SCORE = 750;
	static const int TIME_SCORE = 100;
	static const int HEALTH_SCORE_BONUS = 3000;
	static const int ITEMS_SCORE_BONUS = 4000;
	static const int ENEMIES_SCORE_BONUS = 5000;
	static Game& getInstance();
	Game(Game const&) = delete;
	void operator=(Game const&) = delete;
	void init();
	void run();
	Font& getMainFont();
	Level& getLevel();
	string getNextLevelFilename();
	void nextLevel();
};
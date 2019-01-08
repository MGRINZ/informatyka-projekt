#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameMenu.h"
#include "Level.h"
#include "Save.h"

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
		IN_GAME,
		EXIT
	};
	Status status;
	Save save;
	const int DIFFICULTY_MULTIPLIERS[3] = { 1, 2, 3 };
public:
	static const int WIDTH = 800;
	static const int HEIGHT = 600;
	static const int HEALTH_SCORE = 1000;
	static const int ITEMS_SCORE = 250;
	static const int ENEMIES_SCORE = 500;
	static const int TIME_SCORE = 10;
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
	void startLevel(int levelId);
	void backToMenu();
	void loadSave(Save save);
	Save getSave();
	void exit();
	int getDifficultyMultiplier(int difficulty);
	int getDifficultyMultiplier();
};
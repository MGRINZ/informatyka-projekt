#pragma once

#include "BlocksVector.h"
#include "Entity.h"
#include "Item.h"
#include "Player.h"
#include "Background.h"
#include "LevelEndScreen.h"

class Level
{
private:
	BlocksVector solidBlocks;
	vector<Block> backgroundBlocks;
	vector<Block> foregroundBlocks;
	vector<Entity*> enemies;
	vector<Item> items;
	Player player;
	string name;
	Background background;
	string audio;
	int timeLeft;
	Clock levelClock;
	View view;
	Vector2u endPosition[2];
	LevelEndScreen endScreen;
	int status;

public:
	static const int LEVEL_LOAD_SUCCESS = 0;
	static const int LEVEL_LOAD_ERROR_OPEN_FILE = 1;
	static const string LEVEL_PROPERTY_SETTINGS;
	static const string LEVEL_PROPERTY_TERRAIN;
	static const string LEVEL_PROPERTY_BACKGROUND;
	static const string LEVEL_PROPERTY_FOREGROUND;
	static const string LEVEL_PROPERTY_ITEMS;
	static const string LEVEL_PROPERTY_ENTITIES;
	static const int LEVEL_STATUS_LOADING = 0;
	static const int LEVEL_STATUS_IN_GAME = 1;
	static const int LEVEL_STATUS_PAUSED = 2;
	static const int LEVEL_STATUS_FINISHED = 3;
	Level();
	void addSolidBlock(Block block);
	void addBackgroundBlock(Block block);
	void addForegroundBlock(Block block);
	void addItem(Item item);
	void addEnemy(Entity* entity);
	void draw(RenderWindow &window);
	int load(string levelName);
	void handleEntities();
	void handleItems();
	void handleFinish();
	void handleTimers();
	View getView();
	int getStatus();
	void setStatus(int status);
};
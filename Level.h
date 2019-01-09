#pragma once

#include "BlocksVector.h"
#include "Entity.h"
#include "Projectile.h"
#include "Item.h"
#include "Player.h"
#include "Background.h"
#include "LevelEndScreen.h"
#include "LevelCompleteScreen.h"
#include "LevelFailedScreen.h"
#include "HelpMenu.h"

class Level
{
private:
	string levelFilename;
	BlocksVector solidBlocks;
	vector<Block> backgroundBlocks;
	vector<Block> foregroundBlocks;
	vector<Entity*> enemies;
	vector<Projectile*> projectiles;
	vector<Item*> items;
	Player player;
	string name;
	Background background;
	string audio;
	int timeLeft;
	Clock levelClock;
	View view;
	Vector2u endPosition[2];
	LevelEndScreen *endScreen;
	LevelEndScreen *pauseMenu;
	int status;
	Event *event;
	HelpMenu *helpMenu;
public:
	static const int LEVEL_LOAD_SUCCESS = 0;
	static const int LEVEL_LOAD_ERROR_OPEN_FILE = 1;
	static const string LEVEL_PATH;
	static const string LEVEL_PROPERTY_SETTINGS;
	static const string LEVEL_PROPERTY_TERRAIN;
	static const string LEVEL_PROPERTY_BACKGROUND;
	static const string LEVEL_PROPERTY_FOREGROUND;
	static const string LEVEL_PROPERTY_ITEMS;
	static const string LEVEL_PROPERTY_ENTITIES;
	enum Status {
		LOADING,
		IN_GAME,
		PAUSED,
		HELP_MENU,
		FINISHED,
		FAILED
	};
	Level();
	~Level();
	void addSolidBlock(Block block);
	void addBackgroundBlock(Block block);
	void addForegroundBlock(Block block);
	void addItem(int x, int y, string type);
	void addEnemy(Entity* entity);
	void addProjectile(Projectile* projectile);
	void draw(RenderWindow &window);
	int load(string levelFilename, bool flushTextures = true);
	void restart();
	void resetEndScreen();
	void resetPauseMenu();
	void resetHelpMenu();
	void handleEntities();
	void handleItems();
	void handleFinish();
	void handleTimers();
	void handlePause();
	void setView(View view);
	View getView();
	int getStatus();
	void setStatus(int status);
	string getLevelFilename();
	void setEvent(Event *event);
	void showPauseMenu();
	void showHelpMenu();
	Player & getPlayer();
	int countScore();
};
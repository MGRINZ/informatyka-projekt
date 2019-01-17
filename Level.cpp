#include <iostream>
#include "Level.h"
#include <fstream>
#include <sstream>
#include "IEgg.h"
#include "IHealth.h"
#include "NoFlagException.h"
#include "EJelly.h"
#include "EJumpJelly.h"
#include "EMovingShootingJelly.h"
#include "EShootingJelly.h"
#include "ESleepingJelly.h"
#include "Game.h"
#include "Frame.h"
#include "PauseMenu.h"

using namespace std;

const string Level::LEVEL_PATH = "resources/levels/";
const string Level::LEVEL_PROPERTY_SETTINGS = ";settings";
const string Level::LEVEL_PROPERTY_TERRAIN = ";terrain";
const string Level::LEVEL_PROPERTY_BACKGROUND = ";background";
const string Level::LEVEL_PROPERTY_FOREGROUND = ";foreground";
const string Level::LEVEL_PROPERTY_ITEMS = ";items";
const string Level::LEVEL_PROPERTY_ENTITIES = ";entities";

Level::Level()
{
}

Level::~Level()
{
	if(endScreen != NULL)
		delete endScreen;
	if(pauseMenu != NULL)
		delete pauseMenu;
	if(helpMenu != NULL)
		delete helpMenu;
}

void Level::addSolidBlock(Block block)
{
	solidBlocks.push_back(block);
}

void Level::addBackgroundBlock(Block block)
{
	backgroundBlocks.push_back(block);
}

void Level::addForegroundBlock(Block block)
{
	foregroundBlocks.push_back(block);
}

void Level::addItem(int x, int y, string type)
{
	Item *item = nullptr;
	if (type == "egg")
	{
		item = new IEgg(x, y);
		ItemsBar *itemsBar = player.getHUD()->getItemsBar();
		itemsBar->setItems(itemsBar->getCurrentItems(), itemsBar->getMaxItems() + 1);
	}
	else if (type == "health")
		item = new IHealth(x, y);
	
	if (item != nullptr)
		items.push_back(item);
}

void Level::addEnemy(Entity * entity)
{
	enemies.push_back(entity);
}

void Level::addProjectile(Projectile * projectile)
{
	projectiles.push_back(projectile);
}

void Level::draw(RenderWindow &window)
{
	if (status == Status::LOADING)
		return;
	window.draw(background);

	for (auto &block : backgroundBlocks)
		window.draw(block);
	for (auto &block : solidBlocks)
		window.draw(block);
	for (auto &item : items)
	{
		if (item->isActive())
			window.draw(*item);
	}

	window.draw(player);

	for (auto &enemy : enemies)
		window.draw(*enemy);

	for (auto &projectile : projectiles)
	{
		if (projectile->isActive())
			window.draw(*projectile);
	}

	for (auto &block : foregroundBlocks)
		window.draw(block);

	window.draw(*player.getHUD());

	if (getStatus() == Status::FINISHED || getStatus() == Status::FAILED)
		if(endScreen != NULL)
			endScreen->draw(window);
	if (getStatus() == Status::PAUSED)
		if (pauseMenu != NULL)
			pauseMenu->draw(window);
	if (getStatus() == Status::HELP_MENU)
		if (helpMenu != NULL)
			window.draw(*helpMenu);
}

int Level::load(string levelFilename, bool flushTextures)
{
	status = Status::LOADING;
	
	this->levelFilename = levelFilename;

	if (flushTextures)
	{
		Block::flushTextures();
		Entity::flushTextures();
	}

	for (auto &i : enemies)
		delete i;

	for (auto &i : items)
		delete i;

	solidBlocks.clear();
	backgroundBlocks.clear();
	foregroundBlocks.clear();
	enemies.clear();
	projectiles.clear();
	items.clear();
	player.reset();
	resetEndScreen();
	resetPauseMenu();

	ifstream levelInputStream("resources/levels/" + levelFilename);
	if (!levelInputStream.is_open())
		return LEVEL_LOAD_ERROR_OPEN_FILE;

	string line;
	string property;
	while (getline(levelInputStream, line))
	{
		if (line[0] == ';')
		{
			property = line;
			continue;
		}
		else
		{
			if (property == LEVEL_PROPERTY_SETTINGS)
			{
				int pos = -1;
				if (line.find("name") == 0)
					name = line.substr(5);
				else if (line.find("background") == 0)
				{
					background.setTexture(line.substr(11));
					background.setPosition(Vector2f(0, 0));
				}
				else if (line.find("audio") == 0)
					audio = line.substr(6);
				else if (line.find("start") == 0)
				{
					string startPosition = line.substr(6);
					string x, y;
					stringstream ss;
					ss << startPosition;
					getline(ss, x, ';');
					getline(ss, y, ';');
					player.setPosition(atoi(x.c_str()), atoi(y.c_str()));
				}
				else if (line.find("end") == 0)
				{
					string startPosition = line.substr(4);
					string x, y;
					stringstream ss;
					ss << startPosition;
					getline(ss, x, ';');
					getline(ss, y, ';');
					endPosition[0].x = atoi(x.c_str());
					endPosition[0].y = atoi(y.c_str());
					getline(ss, x, ';');
					getline(ss, y, ';');
					endPosition[1].x = atoi(x.c_str());
					endPosition[1].y = atoi(y.c_str());
				}
				else if (line.find("time") == 0)
				{
					timeLeft = atoi(line.substr(5).c_str());
				}
			}
			else if (property == LEVEL_PROPERTY_TERRAIN || property == LEVEL_PROPERTY_BACKGROUND || property == LEVEL_PROPERTY_FOREGROUND)
			{
				int x, y;
				string texture;
				string token;

				stringstream ss;
				ss << line;
				getline(ss, token, ';');
				x = atoi(token.c_str());
				getline(ss, token, ';');
				y = atoi(token.c_str());
				getline(ss, token, ';');
				texture = token;
				if (property == LEVEL_PROPERTY_TERRAIN)
					addSolidBlock(Block(x, y, texture));
				else if (property == LEVEL_PROPERTY_BACKGROUND)
					addBackgroundBlock(Block(x, y, texture));
				else if (property == LEVEL_PROPERTY_FOREGROUND)
					addForegroundBlock(Block(x, y, texture));

			}
			else if (property == LEVEL_PROPERTY_ITEMS)
			{
				int x, y;
				string type;

				string token;
				stringstream ss;
				ss << line;
				getline(ss, token, ';');
				x = atoi(token.c_str());
				getline(ss, token, ';');
				y = atoi(token.c_str());
				getline(ss, token, ';');
				type = token;

				addItem(x, y, type);
			}
			else if (property == LEVEL_PROPERTY_ENTITIES)
			{
				int x, y;
				string type;
				string flags;

				string token;
				stringstream ss;
				ss << line;
				getline(ss, token, ';');
				x = atoi(token.c_str());
				getline(ss, token, ';');
				y = atoi(token.c_str());
				getline(ss, token, ';');
				type = token;
				getline(ss, token, ';');
				flags = token;

				Entity* enemy = NULL;
				if (type == "jelly")
					enemy = new EJelly();
				else if (type == "jumpjelly")
					enemy = new EJumpJelly();
				else if (type == "sleepingjelly")
					enemy = new ESleepingJelly();
				else if (type == "shootingjelly")
					enemy = new EShootingJelly();
				else if (type == "movingshootingjelly")
					enemy = new EMovingShootingJelly();
				enemy->setPosition(x, y);

				if (!flags.empty())
				{
					ss.str("");
					ss.clear();
					ss << flags;
					while (!ss.eof())
					{
						getline(ss, token, '|');
						try
						{
							enemy->setFlag(token, true);
						}
						catch (NoFlagException &e)
						{
							cout << e.what();
						}
					}
				}

				addEnemy(enemy);
			}
			else
				continue;
		}
	}

	view = View(FloatRect(0, 0, Game::WIDTH, Game::HEIGHT));
	player.getHUD()->getTimeBar()->setTimeLeft(timeLeft);

	status = Status::IN_GAME;
	return LEVEL_LOAD_SUCCESS;
}

void Level::restart()
{
	load(levelFilename, false);
}

void Level::resetEndScreen()
{
	if (endScreen != NULL)
		delete endScreen;
	endScreen = NULL;
}

void Level::resetPauseMenu()
{
	if (pauseMenu != NULL)
		delete pauseMenu;
	pauseMenu = NULL;
}

void Level::resetHelpMenu()
{
	if (helpMenu != NULL)
		delete helpMenu;
	helpMenu = NULL;
}

void Level::handleEntities()
{
	Vector2f ep, pp;
	pp = player.getPosition();

	for (auto &enemy : enemies)
	{
		enemy->handleGravity(solidBlocks);
		enemy->animate();
		enemy->handleMovement(solidBlocks);
		player.takingDamage(*enemy);

		ep = enemy->getPosition();
		
		if (ep.x > pp.x && ep.x - pp.x < Game::WIDTH ||
			ep.x < pp.x && pp.x - ep.x < Game::WIDTH)	//TODO: Do przemyœlenia po utworzeniu pe³nego poziomu
			enemy->activate();
	}

	for (auto &projectile : projectiles)
	{
		projectile->animate();
		projectile->shoot(solidBlocks);
		if (player.takingDamage(*projectile))
			projectile->deactivate();
	}

	player.handleGravity(solidBlocks);
	player.animate();
	player.handleMovement(solidBlocks, view, background);

	player.getHUD()->getEnemiesBar()->setItems(&enemies);
}

void Level::handleItems()
{
	for (auto &item : items)
	{
		item->animate();
		player.takingItem(*item);
	}
}

void Level::handleFinish()
{
	FloatRect gb = player.getGlobalBounds();
	FloatRect endArea(endPosition[0].x * Block::WIDTH, endPosition[0].y * Block::WIDTH, (endPosition[1].x - endPosition[0].x + 1) * Block::WIDTH, (endPosition[1].y - endPosition[0].y + 1) * Block::WIDTH);

	if (gb.intersects(endArea)) {
		setStatus(Status::FINISHED);
		if(endScreen == NULL)
			endScreen = new LevelCompleteScreen(player.getHUD(), view.getCenter());
		Save save = Game::getInstance().getSave();
		int level = atoi(levelFilename.substr(5, 1).c_str());
		if(level == save.getLevel())
			save.setLevel(save.getLevel() + 1);
		int newHighScore = countScore();
		if(save.getHighScore(level - 1) < newHighScore)
			save.setHighScore(level - 1, newHighScore);
		save.write();
		Game::getInstance().loadSave(save);
		
	}
	if(!player.isAlive())
	{
		setStatus(Status::FAILED);
		if (endScreen == NULL)
			endScreen = new LevelFailedScreen(view.getCenter());
	}
}

void Level::handleTimers()
{
	if (levelClock.getElapsedTime().asSeconds() < 1)
		return;

	if (getStatus() == Status::IN_GAME)
	{
		if (timeLeft > 0)
			timeLeft--;
		player.getHUD()->getTimeBar()->setTimeLeft(timeLeft);

		player.immunity();
	}

	levelClock.restart();
}

void Level::handlePause()
{
	if (event != NULL)
	{
		if (event->key.code == Keyboard::Escape)
		{
			if (status == Status::IN_GAME)
			{
				showPauseMenu();
				setStatus(Status::PAUSED);
			}
			else if (status == Status::PAUSED)
			{
				resetPauseMenu();
				setStatus(Status::IN_GAME);
			}
		}
	}
}

void Level::setView(View view)
{
	this->view = view;
}

View Level::getView()
{
	return view;
}

int Level::getStatus()
{
	return status;
}

void Level::setStatus(int status)
{
	this->status = status;
}

string Level::getLevelFilename()
{
	return levelFilename;
}

void Level::setEvent(Event *event)
{
	if (this->event != nullptr)
		delete this->event;

	if (event == nullptr)
		this->event = event;
	else
		this->event = new Event(*event);
}

void Level::showPauseMenu()
{
	pauseMenu = new PauseMenu();
}

void Level::showHelpMenu()
{
	helpMenu = new HelpMenu();
	helpMenu->setPosition(view.getCenter());
}

Player & Level::getPlayer()
{
	return player;
}

int Level::countScore()
{
	HUD *hud = player.getHUD();
	int health = hud->getHealthBar()->getHealth();
	int items = hud->getItemsBar()->getCurrentItems();
	int enemies = hud->getEnemiesBar()->getCurrentItems();
	int timeLeft = hud->getTimeBar()->getTimeLeft();
	int difficultyMultiplier = Game::getInstance().getDifficultyMultiplier();

	int score = 0;

	score += health * Game::HEALTH_SCORE;
	if(health == hud->getHealthBar()->getMaxHealth())
		score += Game::HEALTH_SCORE_BONUS;

	score += items * Game::ITEMS_SCORE;
	if (items == hud->getItemsBar()->getMaxItems())
		score += Game::ITEMS_SCORE_BONUS;

	score += enemies * Game::ENEMIES_SCORE;
	if (enemies == hud->getEnemiesBar()->getMaxItems())
		score += Game::ENEMIES_SCORE_BONUS;

	score += timeLeft * Game::TIME_SCORE;

	score *= difficultyMultiplier;
	return score;
}

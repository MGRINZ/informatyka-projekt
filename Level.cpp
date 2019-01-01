#include <iostream>
#include "Level.h"
#include <fstream>
#include <sstream>
#include "EJelly.h"
#include "EJumpJelly.h"
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

void Level::addItem(Item item)
{
	items.push_back(item);
}

void Level::addEnemy(Entity * entity)
{
	enemies.push_back(entity);
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
		if (item.isActive())
			window.draw(item);
	}

	window.draw(player);

	for (auto &enemy : enemies)
		window.draw(*enemy);

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

int Level::load(string levelFilename)
{
	status = Status::LOADING;
	
	this->levelFilename = levelFilename;

	solidBlocks.clear();
	backgroundBlocks.clear();
	foregroundBlocks.clear();
	enemies.clear();
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
				addItem(Item(x, y, "egg1.png"));
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
				enemy->setPosition(x, y);

				if (!flags.empty())
				{
					ss.str("");
					ss.clear();
					ss << flags;
					while (!ss.eof())
					{
						getline(ss, token, '|');
						enemy->setFlag(token, true);
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
	load(levelFilename);
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
	for (auto &enemy : enemies)
	{
		enemy->handleGravity(solidBlocks);
		enemy->animate();
		enemy->handleMovement(solidBlocks);
		player.takingDamage(*enemy);
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
		item.animate();
		player.takingItem(item);
	}
	player.getHUD()->getItemsBar()->setItems(&items);
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
		if(atoi(levelFilename.substr(5, 1).c_str()) == save.getLevel())
			save.setLevel(save.getLevel() + 1);
		save.write();
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
}

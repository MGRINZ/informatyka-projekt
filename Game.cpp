#include <iostream>
#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace std;
using namespace sf;

const float Block::WIDTH = Game::HEIGHT / 18.75;
const float Entity::WIDTH = Block::WIDTH;
const string Level::LEVEL_PROPERTY_SETTINGS = ";settings";
const string Level::LEVEL_PROPERTY_TERRAIN = ";terrain";
const string Level::LEVEL_PROPERTY_BACKGROUND = ";background";
const string Level::LEVEL_PROPERTY_FOREGROUND = ";foreground";
const string Level::LEVEL_PROPERTY_ITEMS = ";items";
const string Level::LEVEL_PROPERTY_ENTITIES = ";entities";

Level::Level()
{
	addBackgroundBlock(Block(endPosition[0].x, endPosition[0].y));
	addBackgroundBlock(Block(endPosition[1].x, endPosition[1].y));
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

void Level::draw(RenderWindow &window)
{
	window.draw(background);

	for (auto &block : backgroundBlocks)
		window.draw(block);
	for (auto &block : solidBlocks)
		window.draw(block);
	for (auto &item : items)
	{
		if(item.isActive())
			window.draw(item);
	}
	
	window.draw(player);

	for (auto &block : foregroundBlocks)
		window.draw(block);

	hud.draw(window);

	if(getStatus() == LEVEL_STATUS_FINISHED)
		endScreen.draw(window);
}

int Level::load(string levelName)
{
	status = LEVEL_STATUS_LOADING;

	solidBlocks.clear();
	backgroundBlocks.clear();
	foregroundBlocks.clear();
	enemies.clear();
	items.clear();
	player.reset();
	hud.setPosition(Vector2f(50, 20));

	ifstream levelInputStream("resources/levels/" + levelName);
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
				if(property == LEVEL_PROPERTY_TERRAIN)
					addSolidBlock(Block(x, y, texture));
				else if(property == LEVEL_PROPERTY_BACKGROUND)
					addBackgroundBlock(Block(x, y, texture));
				else if(property == LEVEL_PROPERTY_FOREGROUND)
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
			else
				continue;
		}
	}

	view = View(FloatRect(0, 0, Game::WIDTH, Game::HEIGHT));
	status = LEVEL_STATUS_IN_GAME;
	return LEVEL_LOAD_SUCCESS;
}

void Level::handleEntities()
{
	for (auto &enemy : enemies)
	{
		enemy.handleGravity(solidBlocks);
	}
	player.handleGravity(solidBlocks);
	player.animate();
	player.handleMovement(solidBlocks, view, background, hud);
}

void Level::handleItems()
{
	for (auto &item : items)
	{
		item.animate();
		player.takingItem(item);
	}
	hud.getItemsBar()->setItems(&items);
}

void Level::handleFinish()
{
	FloatRect gb = player.getGlobalBounds();
	FloatRect endArea(endPosition[0].x * Block::WIDTH, endPosition[0].y * Block::WIDTH, (endPosition[1].x - endPosition[0].x + 1) * Block::WIDTH, (endPosition[1].y - endPosition[0].y + 1) * Block::WIDTH);
	
	if (!gb.intersects(endArea))
		return;

	setStatus(LEVEL_STATUS_FINISHED);
	endScreen.setPosition(view.getCenter());

	if (Keyboard::isKeyPressed(Keyboard::Enter))
		load("level3.lvl");
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

void Entity::handleGravity(BlocksVector &blocks, float gravity)
{
	Vector2f entityPosition = getPosition();
	float eX = entityPosition.x;
	float eY = entityPosition.y;

	Block *blockDL = blocks.getSolidBlockAtPosition((eX - WIDTH / 2) / Block::WIDTH, (eY - WIDTH + Block::WIDTH) / Block::WIDTH);
	Block *blockDR = blocks.getSolidBlockAtPosition((eX + WIDTH / 2 - 1) / Block::WIDTH, (eY - WIDTH + Block::WIDTH) / Block::WIDTH);
	
	Block *blockUL = blocks.getSolidBlockAtPosition((eX - WIDTH / 2) / Block::WIDTH, (eY - WIDTH + ((yVelocityDown + yVelocityUp) + 0.025) * Block::WIDTH) / Block::WIDTH);
	Block *blockUR = blocks.getSolidBlockAtPosition((eX + WIDTH / 2 - 1) / Block::WIDTH, (eY - WIDTH + ((yVelocityDown + yVelocityUp) + 0.025) * Block::WIDTH) / Block::WIDTH);

	if (blockUL != NULL || blockUR != NULL)
	{
		yVelocityUp = 0.0;
		yVelocityDown = 0.0;
		jumping = false;
		setMovingDirectionY(0);
	}


	if (blockDL != NULL || blockDR != NULL)
	{
		Sprite::setPosition(Vector2f(eX, (int)(eY / Block::WIDTH) * Block::WIDTH));
		yVelocityDown = 0.0;
		yVelocityUp = 0.0;
		setMovingDirectionY(0);
		return;
	}

	if(yVelocityDown == yVelocityUp)
		yVelocityDown = 0.0;

	yVelocityDown += gravity * 0.0017;
	move(Vector2f(0, (yVelocityDown + yVelocityUp) * Block::WIDTH));
	if (yVelocityDown + yVelocityUp > 0)
		setMovingDirectionY(1);
	else if(yVelocityDown + yVelocityUp < 0)
		setMovingDirectionY(-1);
}

void Entity::handleMovement(BlocksVector &solidBlocks, View &view, Sprite &background, HUD &hud)
{
	Vector2f velocity(0, 0);
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		if (canGoRight(solidBlocks))
		{
			velocity = Vector2f(Block::WIDTH / 8, 0);
			setMovingDirectionX(1);

			
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		if (canGoLeft(solidBlocks))
		{
			velocity = Vector2f(-Block::WIDTH / 8, 0);
			setMovingDirectionX(-1);
		}
	}

	move(velocity);
	if ((getMovingDirectionX() == 1 && getPosition().x > view.getCenter().x + Game::WIDTH / 2 - Game::WIDTH * 0.2) || (getMovingDirectionX() == -1 && getPosition().x < view.getCenter().x - Game::WIDTH / 2 + Game::WIDTH * 0.2))
	{
		view.move(velocity);
		background.move(velocity);
		hud.move(velocity);
	}

	if (!Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Left))
		setMovingDirectionX(0);
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		jump(solidBlocks);
	}
	if (!Keyboard::isKeyPressed(Keyboard::Up))
	{
		setJumping(false);
	}

	//cout << (int) (getPosition().x / WIDTH) << ";" << (int) (getPosition().y / WIDTH) << endl; //Debug: player position
}

bool Entity::canGoRight(BlocksVector &blocks)
{
	Vector2f entityPosition = getPosition();
	float eX = entityPosition.x;
	float eY = entityPosition.y;

	Block *blockU = blocks.getSolidBlockAtPosition((eX - WIDTH / 2 + Block::WIDTH) / Block::WIDTH, (eY - WIDTH) / Block::WIDTH);
	Block *blockD = blocks.getSolidBlockAtPosition((eX - WIDTH / 2 + Block::WIDTH) / Block::WIDTH, (eY - 1) / Block::WIDTH);

	if (blockU == NULL && blockD == NULL)
		return true;

	return false;
}

bool Entity::canGoLeft(BlocksVector &blocks)
{
	Vector2f entityPosition = getPosition();
	float eX = entityPosition.x;
	float eY = entityPosition.y;

	Block *blockU = blocks.getSolidBlockAtPosition((eX + WIDTH / 2 - Block::WIDTH - 4) / Block::WIDTH, (eY - WIDTH) / Block::WIDTH);	// - 4 (prêdkoœæ w piks)
	Block *blockD = blocks.getSolidBlockAtPosition((eX + WIDTH / 2 - Block::WIDTH - 4) / Block::WIDTH, (eY - 1) / Block::WIDTH);		// - 4 (prêdkoœæ w piks)

	if (blockU == NULL && blockD == NULL)
		return true;

	return false;
}

void Entity::jump(BlocksVector &blocks)
{
	if (!isJumping() && yVelocityDown > 0)
		return;
	if (yVelocityUp == 0)
		yVelocityUp = -0.27;
	else if(yVelocityUp > -0.37)
		yVelocityUp -= 10 * 0.001;
	move(Vector2f(0, -0.025 * Block::WIDTH));
	jumping = true;
}

void Entity::setJumping(bool jumping)
{
	this->jumping = jumping;
}

bool Entity::isJumping()
{
	return jumping;
}

Block::Block(int x, int y)
{
	setSize(Vector2f(WIDTH, WIDTH));
	setPosition(x, y);
}

Block::Block(int x, int y, string txt) : Block(x, y)
{
	texture->loadFromFile("resources/textures/blocks/" + txt);
	setTexture(texture);
}

void Block::setPosition(int x, int y)
{
	RectangleShape::setPosition(Vector2f(x * WIDTH, y * WIDTH));
}

Block* BlocksVector::getSolidBlockAtPosition(int x, int y)
{
	for (auto &block : *this)
	{
		Vector2f blockPosition = block.getPosition();
		if (blockPosition.x == x * Block::WIDTH && blockPosition.y == y * Block::WIDTH)
			return &block;
	}
	return nullptr;
}

Background::Background()
{
	
}

void Background::setTexture(String texture)
{
	name = texture;
	if(!texture.isEmpty())
	{
		this->texture.loadFromFile("resources/backgrounds/" + texture);
		Sprite::setTexture(this->texture);
	}
}

void Entity::animate()
{
	if(isMovingY) {		
		IntRect txtRect = getTextureRect();
		txtRect.left = 6 * WIDTH;
		if(isMovingX == 1)
			txtRect.top = 0;
		else if (isMovingX == -1)
			txtRect.top = WIDTH;
		setTextureRect(txtRect);
		return;
	}

	if(!isMovingX) {
		IntRect txtRect = getTextureRect();
		txtRect.left = 0;
		setTextureRect(txtRect);
		return;
	}

	if (animateClock.getElapsedTime().asMilliseconds() >= 50)
	{
		IntRect txtRect = getTextureRect();
		txtRect.left += WIDTH * ((txtRect.left / WIDTH) + 1);
		if (txtRect.left >= 5 * WIDTH)
			txtRect.left = 0;
		if (isMovingX == 1)
			txtRect.top = 0;
		else if (isMovingX == -1)
			txtRect.top = WIDTH;
		setTextureRect(txtRect);
		animateClock.restart();
	}
}

void Entity::setMovingDirectionX(int x)
{
	isMovingX = x;
}

void Entity::setMovingDirectionY(int y)
{
	isMovingY = y;
}

int Entity::getMovingDirectionX()
{
	return isMovingX;
}

int Entity::getMovingDirectionY()
{
	return isMovingY;
}

void Entity::takingItem(Item &item)
{
	FloatRect gb = item.getGlobalBounds();
	if (getGlobalBounds().intersects(gb))
		item.disable();
}

Entity::Entity()
{
	setOrigin(Vector2f(WIDTH / 2, WIDTH));
	texture.loadFromFile("resources/textures/easteregg-man.png");
	setTexture(texture);
	setTextureRect(IntRect(0, 0, WIDTH, WIDTH));
	reset();
}

void Entity::reset()
{
	yVelocityDown = 0.0;
	yVelocityUp = 0.0;
	jumping = false;
	isMovingX = 0;
	isMovingY = 0;
}

void Entity::setPosition(int x, int y)
{
	Sprite::setPosition(Vector2f(x * WIDTH + WIDTH / 2, y * WIDTH + WIDTH));
}

Item::Item(int x, int y) : Block(x, y)
{

}

Item::Item(int x, int y, string txt) : Block(x, y)
{
	texture->loadFromFile("resources/textures/" + txt);
	setTexture(texture);
	setTextureRect(IntRect(0, 0, WIDTH, WIDTH));
}

bool Item::isActive()
{
	return active;
}

void Item::disable()
{
	active = false;
}

void Item::animate()
{
	Vector2u txtSize = texture->getSize();
	if (animateClock.getElapsedTime().asMilliseconds() >= 100)
	{
		IntRect txtRect = getTextureRect();
		txtRect.left += WIDTH * ((txtRect.left / WIDTH) + 1);
		if (txtRect.left >= txtSize.x)
			txtRect.left = 0;
		setTextureRect(txtRect);
		animateClock.restart();
	}
}

LevelEndScreen::LevelEndScreen()
{
	FloatRect gb;

	overlay.setFillColor(Color(0,0,0,192));
	overlay.setSize(Vector2f(Game::WIDTH, Game::HEIGHT));
	
	container.setFillColor(Color::Blue);
	container.setOrigin(Vector2f(Game::WIDTH * 0.8 / 2, Game::HEIGHT * 0.5 / 2));
	container.setSize(Vector2f(Game::WIDTH * 0.8, Game::HEIGHT * 0.5));
	
	headerFont.loadFromFile("resources/fonts/verdana.ttf");
	
	header.setFont(headerFont);
	header.setString("Poziom ukonczony");
	gb = header.getGlobalBounds();
	header.setOrigin(Vector2f(gb.width / 2, gb.height / 2));

	setPosition(Vector2f(0, 0));
}

void LevelEndScreen::draw(RenderWindow & window)
{
	window.draw(overlay);
	window.draw(container);
	window.draw(header);
}

void LevelEndScreen::setPosition(Vector2f position)
{
	this->position = position;
	overlay.setPosition(Vector2f(position.x - Game::WIDTH / 2, position.y - Game::HEIGHT / 2));
	container.setPosition(Vector2f(position.x, position.y));
	header.setPosition(Vector2f(position.x, position.y - 120));
}

HUD::HUD()
{
	setPosition(Vector2f(50, 20));
}

void HUD::draw(RenderWindow & window)
{
	healthBar.draw(window);
	itemsBar.draw(window);
}

void HUD::setPosition(Vector2f position)
{
	healthBar.setPosition(Vector2f(position));
	itemsBar.setPosition(Vector2f(position.x + 200, position.y));
}

void HUD::move(Vector2f position)
{
	healthBar.move(position);
	itemsBar.move(position);
}

HealthBar * HUD::getHealthBar()
{
	return &healthBar;
}

ItemsBar * HUD::getItemsBar()
{
	return &itemsBar;
}

HealthBar::HealthBar()
{
	healthTexture.loadFromFile("resources/textures/health.png");
	healthTextureEmpty.loadFromFile("resources/textures/health_empty.png");
	for (int i = 0; i < maxHealth; i++)
		health[i].setScale(Vector2f(1.5, 1.5));
	setHealth(3);
}

void HealthBar::draw(RenderWindow & window)
{
	for(int i = 0; i < maxHealth; i++)
		window.draw(health[i]);
}

void HealthBar::setHealth(int hp)
{
	for (int i = 0; i < maxHealth; i++)
	{
		if (i < hp)
			health[i].setTexture(healthTexture);
		else
			health[i].setTexture(healthTextureEmpty);
	}
}

void HealthBar::setMaxHealth(int maxHealth)
{
	this->maxHealth = maxHealth;
}

void HealthBar::setPosition(Vector2f position)
{
	this->position = position;
	for (int i = 0; i < maxHealth; i++)
		health[i].setPosition(Vector2f(position.x + i * 50, position.y));
}

void HealthBar::move(Vector2f position)
{
	this->position.x += position.x;
	this->position.y += position.y;
	for (int i = 0; i < maxHealth; i++)
		health[i].move(position);
}

ItemsBar::ItemsBar()
{
	itemsTexture.loadFromFile("resources/textures/egg1.png");
	item.setTexture(itemsTexture);
	item.setTextureRect(IntRect(0, 0, 32, 32));
	item.setScale(Vector2f(1.5, 1.5));

	itemCounterFont.loadFromFile("resources/fonts/verdana.ttf");
	itemCounter.setFont(itemCounterFont);
	itemCounter.setOutlineColor(Color::Black);
	itemCounter.setOutlineThickness(1);
}

void ItemsBar::draw(RenderWindow & window)
{
	window.draw(item);
	window.draw(itemCounter);
}

void ItemsBar::setPosition(Vector2f position)
{
	item.setPosition(position);
	itemCounter.setPosition(Vector2f(position.x + 50, position.y + 4));
}

void ItemsBar::move(Vector2f position)
{
	item.move(position);
	itemCounter.move(position);
}

void ItemsBar::setItems(vector<Item>* items)
{
	this->items = items;
	int count = 0;
	for (auto &item : *items)
	{
		if (!item.isActive())
			count++;
	}

	stringstream ss;
	ss << count << "/" << items->size();
	itemCounter.setString(ss.str());
}

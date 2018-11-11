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
	load("level3.lvl");
	player.setPosition(5, 9);
	view = View(FloatRect(0, 0, Game::WIDTH, Game::HEIGHT));
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
}

int Level::load(string levelName)
{
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
					background.setTexture(line.substr(11));
				else if (line.find("audio") == 0)
					audio = line.substr(6);
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
	

	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		if (player.canGoRight(solidBlocks))
		{
			player.move(Vector2f(Block::WIDTH / 8, 0));
			player.setMovingDirectionX(1);

			if (player.getPosition().x > view.getCenter().x + Game::WIDTH / 2 - Game::WIDTH * 0.2)
			{
				view.move(Vector2f(Block::WIDTH / 8, 0));
				background.move(Vector2f(Block::WIDTH / 8, 0));
			}
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		if (player.canGoLeft(solidBlocks))
		{
			player.move(Vector2f(-Block::WIDTH / 8, 0));
			player.setMovingDirectionX(-1);

			if (player.getPosition().x < view.getCenter().x - Game::WIDTH / 2 + Game::WIDTH * 0.2)
			{
				view.move(Vector2f(-Block::WIDTH / 8, 0));
				background.move(Vector2f(-Block::WIDTH / 8, 0));
			}
		}
	}
	if (!Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Left))
		player.setMovingDirectionX(0);
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		player.jump(solidBlocks);
	}
	if (!Keyboard::isKeyPressed(Keyboard::Up))
	{
		player.setJumping(false);
	}
}

void Level::handleItems()
{
	for (auto &item : items)
	{
		item.animate();
	}
	player.takingItem(items);
}

View Level::getView()
{
	return view;
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

void Entity::takingItem(vector<Item> &items)
{
	for (auto &item : items)
	{
		FloatRect gb = item.getGlobalBounds();
		if (getGlobalBounds().intersects(gb))
		{
			item.disable();
			break;
		}
	}
}

Entity::Entity()
{
	setOrigin(Vector2f(WIDTH / 2, WIDTH));
	texture.loadFromFile("resources/textures/easteregg-man.png");
	setTexture(texture);
	setTextureRect(IntRect(0, 0, WIDTH, WIDTH));
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

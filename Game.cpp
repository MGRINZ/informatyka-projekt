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
const string Level::LEVEL_PROPERTY_ENTITIES = ";entities";

Level::Level()
{
	load("level2.lvl");
	player.setPosition(5, 9);
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

void Level::draw(RenderWindow &window)
{
	window.draw(background);

	for (auto &block : backgroundBlocks)
		window.draw(block);
	for (auto &block : solidBlocks)
		window.draw(block);
	
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
			if (property == LEVEL_PROPERTY_TERRAIN || property == LEVEL_PROPERTY_BACKGROUND || property == LEVEL_PROPERTY_FOREGROUND)
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

	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		if(player.canGoRight(solidBlocks))
			player.move(Vector2f(Block::WIDTH / 8, 0));
	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		if (player.canGoLeft(solidBlocks))
			player.move(Vector2f(-Block::WIDTH / 8, 0));
	}
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		player.jump(solidBlocks);
	}
	if (!Keyboard::isKeyPressed(Keyboard::Up))
	{
		
	}
}

void Entity::handleGravity(BlocksVector &blocks, float gravity)
{
	static int i = 0;
	Vector2f entityPosition = getPosition();
	float eX = entityPosition.x;
	float eY = entityPosition.y;

	Block *blockL = blocks.getSolidBlockAtPosition((eX - WIDTH / 2) / Block::WIDTH, (eY - WIDTH + Block::WIDTH) / Block::WIDTH);
	Block *blockR = blocks.getSolidBlockAtPosition((eX + WIDTH / 2 - 1) / Block::WIDTH, (eY - WIDTH + Block::WIDTH) / Block::WIDTH);

	if (blockL != NULL || blockR != NULL)
	{
		Sprite::setPosition(Vector2f(eX, (int)(eY / Block::WIDTH) * Block::WIDTH));
		yVelocityDown = 0.0;
		yVelocityUp = 0.0;
		return;
	}

	if(yVelocityDown == yVelocityUp)
		yVelocityDown = 0.0;

	yVelocityDown += gravity * 0.001;
	move(Vector2f(0, (yVelocityDown + yVelocityUp) * Block::WIDTH));
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
	if (yVelocityUp == 0)
		yVelocityUp = -0.2;
	else if(yVelocityUp > -0.3)
		yVelocityUp -= 10 * 0.001;
	move(Vector2f(0, -0.025 * Block::WIDTH));
}

Block::Block(int x, int y)
{
	setSize(Vector2f(WIDTH, WIDTH));
	setPosition(x, y);
}

Block::Block(int x, int y, string txt) : Block(x, y)
{
	texture->loadFromFile("resources/textures/" + txt);
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

Entity::Entity()
{
	setOrigin(Vector2f(WIDTH / 2, WIDTH));
	setTexture(texture);
	setTextureRect(IntRect(0, 0, WIDTH, WIDTH));
	yVelocityDown = 0.0;
	yVelocityUp = 0.0;
}

void Entity::setPosition(int x, int y)
{
	Sprite::setPosition(Vector2f(x * WIDTH + WIDTH / 2, y * WIDTH + WIDTH));
}

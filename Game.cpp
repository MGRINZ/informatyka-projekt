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
	player.setPosition(6, 12);
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
}

void Entity::handleGravity(vector<Block> &blocks, float gravity)
{
	Vector2f entityPosition = getPosition();
	int eX = rint(entityPosition.x);
	int eY = rint(entityPosition.y);

	for (auto &block : blocks)
	{
		Vector2f blockPosition = block.getPosition();

		//Bierzemy pod uwagê tylko te bloki poni¿ej obiektu
		if (blockPosition.y + Block::WIDTH <= eY - WIDTH)
			continue;

		//dolna krawêdŸ obiektu styka siê z górn¹ krawêdzi¹ bloku && prawa krawêdŸ obiektu znajduje siê na górnej krawêdzi bloku && lewa krawêdŸ obiektu znajduje siê na górnej krawêdzi bloku
		if (eY >= blockPosition.y && eX + WIDTH / 2 > blockPosition.x && eX - WIDTH / 2 < blockPosition.x + Block::WIDTH)
			return;
	}
	
	move(Vector2f(0, gravity));
}

bool Entity::canGoRight(vector<Block> &blocks)
{
	Vector2f entityPosition = getPosition();
	int eX = rint(entityPosition.x);
	int eY = rint(entityPosition.y);

	for (auto &block : blocks)
	{
		Vector2f blockPosition = block.getPosition();

		//Bierzemy pod uwagê tylko te bloki po prawej stronie obiektu
		if (blockPosition.x < eX + WIDTH / 2)
			continue;

		//prawa krawêdŸ obiektu styka siê z lew¹ krawêdzi¹ bloku && górna krawêdŸ obiektu jest powy¿ej dolnej krawêdzi bloku && dolna krawêdŸ obiektu jest poni¿ej górnej krawêdzi bloku
		if (eX + WIDTH / 2 >= blockPosition.x && eY - WIDTH < blockPosition.y + Block::WIDTH && eY > blockPosition.y)
			return false;
	}

	return true;
}

bool Entity::canGoLeft(vector<Block> &blocks)
{
	Vector2f entityPosition = getPosition();
	int eX = rint(entityPosition.x);
	int eY = rint(entityPosition.y);

	for (auto &block : blocks)
	{
		Vector2f blockPosition = block.getPosition();

		//Bierzemy pod uwagê tylko te bloki po lewej stronie obiektu
		if (blockPosition.x + Block::WIDTH > eX - WIDTH / 2)
			continue;

		//lewa krawêdŸ obiektu styka siê z praw¹ krawêdzi¹ bloku && górna krawêdŸ obiektu jest powy¿ej dolnej krawêdzi bloku && dolna krawêdŸ obiektu jest poni¿ej górnej krawêdzi bloku
		if (eX - WIDTH / 2 <= blockPosition.x + Block::WIDTH && eY - WIDTH < blockPosition.y + Block::WIDTH && eY > blockPosition.y)
			return false;
	}

	return true;
}

void Entity::jump(vector<Block> &blocks)
{
	static bool max_height = false;
	move(Vector2f(0, -Block::WIDTH));
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
}

void Entity::setPosition(int x, int y)
{
	Sprite::setPosition(Vector2f(x * WIDTH + WIDTH / 2, y * WIDTH + WIDTH));
}
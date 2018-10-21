#include <iostream>
#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace std;
using namespace sf;

const string Level::LEVEL_PROPERTY_TERRAIN = ";terrain";

Level::Level()
{
	load("level1.lvl");
}

void Level::addBlock(Block block)
{
	blocks.push_back(block);
}

void Level::draw(RenderWindow &window)
{
	for (auto &block : blocks)
	{
		window.draw(block);
	}
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
			if (property == LEVEL_PROPERTY_TERRAIN)
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
				addBlock(Block(x, y, texture));
			}
			else
				continue;
		}
	}
	return LEVEL_LOAD_SUCCESS;
}


Block::Block(int x, int y)
{
	setSize(Vector2f(width, width));
	setPosition(x, y);
}

Block::Block(int x, int y, string txt) : Block(x, y)
{
	texture->loadFromFile("resources/textures/" + txt);
	setTexture(texture);
}

void Block::setPosition(int x, int y)
{
	RectangleShape::setPosition(Vector2f(x * width, y * width));
}

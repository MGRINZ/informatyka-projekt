#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace std;
using namespace sf;

Level::Level()
{
	for (int i = 0; i < 10; i++) {
		addBlock(Block(0, i, "dirt.jpg"));
		addBlock(Block(i, 0));
		addBlock(Block(i, i));
	}
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

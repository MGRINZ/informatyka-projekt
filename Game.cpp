#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace std;
using namespace sf;

Level::Level()
{
	for (int i = 0; i < 50; i++) {
		addBlock(Block(0, i));
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
	this->setSize(Vector2f(width, width));
	this->setPosition(Vector2f(x * width, y * width));
	this->setOutlineColor(Color::Red);
	this->setOutlineThickness(1.0);
	
}

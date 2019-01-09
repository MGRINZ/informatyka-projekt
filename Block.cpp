#include "Block.h"
#include "Game.h"

map<string, Texture*> Block::textures;

const float Block::WIDTH = Game::HEIGHT / 18.75;

Block::Block(int x, int y)
{
	setSize(Vector2f(WIDTH, WIDTH));
	setPosition(x, y);
}

Block::Block(int x, int y, string txt) : Block(x, y)
{
	loadTexture(RES_DIR + txt);
	setTexture(texture);
}

void Block::setPosition(int x, int y)
{
	RectangleShape::setPosition(Vector2f(x * WIDTH, y * WIDTH));
}

void Block::flushTextures()
{
	for (auto &pair : textures)
		delete pair.second;
	textures.clear();
}

void Block::loadTexture(string texture)
{
	if (!textures.count(texture))
	{
		this->texture = new Texture();
		this->texture->loadFromFile(texture);
		textures.insert(pair<string, Texture*>(texture, this->texture));
	}
	else
		this->texture = textures.at(texture);
}

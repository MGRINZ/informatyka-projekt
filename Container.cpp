#include "Container.h"
#include <iostream>

Container::Container()
{
	setSize(Vector2f(1, 1));
}

Container::Container(Vector2f size)
{
	setSize(size);
}

void Container::draw()
{
	texture.clear(background);
	for (auto &drawable : drawables)
		texture.draw(*drawable);
	texture.display();
}

void Container::setBackground(Color background)
{
	this->background = background;
}

const Texture * Container::getTexture()
{
	return &texture.getTexture();
}

void Container::setSize(Vector2f size)
{
	this->size = size;
	texture.create(size.x, size.y);
}

Vector2f Container::getSize()
{
	return size;
}

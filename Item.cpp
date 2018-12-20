#include "Item.h"

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

#include "Item.h"

Item::Item(int x, int y) : Block(x, y)
{
	onPickUpListener = nullptr;
}

Item::Item(int x, int y, string txt) : Item(x, y)
{
	loadTexture(RES_DIR + txt);
	setTexture(texture);
	setTextureRect(IntRect(0, 0, WIDTH, WIDTH));
}

Item::~Item()
{
	if(onPickUpListener != NULL)
		delete onPickUpListener;
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

void Item::triggerOnPickupEvent()
{
	if(onPickUpListener != nullptr)
		onPickUpListener->onPickUp(*this);
}

void Item::setOnPickUpListener(ItemOnPickUpListener & onPickUpListener)
{
	if (this->onPickUpListener != NULL && &onPickUpListener != this->onPickUpListener)
		delete this->onPickUpListener;
	this->onPickUpListener = &onPickUpListener;
}

#pragma once

class Item;

class ItemOnPickUpListener
{
public:
	virtual void onPickUp(Item &item) = 0;
};
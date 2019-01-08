#pragma once
#include "ItemOnPickUpListener.h"
#include "Item.h"

class IEggOnPickUpListener : public ItemOnPickUpListener
{
public:
	void onPickUp(Item &item);
};


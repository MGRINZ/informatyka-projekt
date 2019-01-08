#pragma once
#include "ItemOnPickUpListener.h"
#include "Item.h"

class IHealthOnPickUpListener : public ItemOnPickUpListener
{
public:
	void onPickUp(Item &item);
};
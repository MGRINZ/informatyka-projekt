#pragma once
#include "Item.h"
#include "IEggOnPickUpListener.h"

class IEgg : public Item
{
private:
	IEggOnPickUpListener *onPickUpListener;
public:
	IEgg(int x, int y);
};


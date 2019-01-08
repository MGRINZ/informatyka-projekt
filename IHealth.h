#pragma once
#include "Item.h"
#include "IHealthOnPickUpListener.h"

class IHealth : public Item
{
private:
	IHealthOnPickUpListener *onPickUpListener;
public:
	IHealth(int x, int y);
};


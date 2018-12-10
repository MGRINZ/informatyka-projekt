#include "ItemsBar.h"
#include <sstream>

ItemsBar::ItemsBar() : HUDBar()
{
	iconTexture.loadFromFile("resources/textures/hud/egg.png");
	icon.setTexture(iconTexture);
}

void ItemsBar::setItems(vector<Item>* items)
{
	int count = 0;
	for (auto &item : *items)
	{
		if (!item.isActive())
			count++;
	}

	HUDBar::setItems(count, items->size());
}
#include "ItemsBar.h"
#include <sstream>

ItemsBar::ItemsBar() : HUDBar()
{
	iconTexture.loadFromFile("resources/textures/hud/egg.png");
	icon.setTexture(iconTexture);
}

void ItemsBar::setItems(vector<Item>* items)
{
	this->items = items;
	int count = 0;
	for (auto &item : *items)
	{
		if (!item.isActive())
			count++;
	}

	stringstream ss;
	ss << count << "/" << items->size();
	counter.setString(ss.str());
}

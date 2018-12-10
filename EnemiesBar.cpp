#include "EnemiesBar.h"
#include <sstream>

EnemiesBar::EnemiesBar() : HUDBar()
{
	iconTexture.loadFromFile("resources/textures/hud/enemy.png");
	icon.setTexture(iconTexture);
}

void EnemiesBar::setItems(vector<Entity*>* items)
{
	int count = 0;
	for (auto &item : *items)
	{
		if (!item->isAlive())
			count++;
	}

	HUDBar::setItems(count, items->size());
}
#pragma once

#include "HUDBar.h"
#include "Entity.h"

class EnemiesBar : public HUDBar
{
private:
	vector <Entity*>* items;
public:
	EnemiesBar();
	void setItems(vector<Entity*>* items);
};

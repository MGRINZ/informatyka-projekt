#pragma once

#include "HUDBar.h"
#include "Entity.h"

class EnemiesBar : public HUDBar
{
public:
	EnemiesBar();
	void setItems(vector<Entity*>* items);
};

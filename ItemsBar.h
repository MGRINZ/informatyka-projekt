#pragma once

#include "HUDBar.h"

class ItemsBar : public HUDBar
{
public:
	ItemsBar();
	void setItems(vector<Item>* items);
};
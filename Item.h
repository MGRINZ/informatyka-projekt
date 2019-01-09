#pragma once
#include <SFML/Graphics.hpp>
#include "Block.h"
#include "ItemOnPickUpListener.h"

using namespace std;
using namespace sf;

class Item : public Block
{
private:
	const string RES_DIR = "resources/textures/";
	bool active = true;
	Clock animateClock;
	ItemOnPickUpListener *onPickUpListener;
public:
	Item(int x, int y);
	Item(int x, int y, string texture);
	~Item();
	bool isActive();
	void disable();
	void animate();
	void triggerOnPickupEvent();
	void setOnPickUpListener(ItemOnPickUpListener &onPickUpListener);
};


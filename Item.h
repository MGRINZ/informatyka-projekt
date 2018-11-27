#pragma once
#include <SFML/Graphics.hpp>
#include "Block.h"

using namespace std;
using namespace sf;

class Item : public Block
{
private:
	const string RES_DIR = "resources/textures/";
	bool active = true;
	Clock animateClock;
public:
	Item(int x, int y);
	Item(int x, int y, string texture);
	bool isActive();
	void disable();
	void animate();
};


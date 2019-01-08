#include "ItemsBar.h"
#include <sstream>

ItemsBar::ItemsBar() : HUDBar()
{
	iconTexture.loadFromFile("resources/textures/hud/egg.png");
	icon.setTexture(iconTexture);
}
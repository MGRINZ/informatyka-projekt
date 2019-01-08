#include "IEgg.h"

IEgg::IEgg(int x, int y) : Item(x, y, "egg1.png")
{
	onPickUpListener = new IEggOnPickUpListener();
	setOnPickUpListener(*onPickUpListener);
}
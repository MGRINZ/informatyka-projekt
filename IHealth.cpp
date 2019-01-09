#include "IHealth.h"

IHealth::IHealth(int x, int y) : Item(x, y, "health.png")
{
	onPickUpListener = new IHealthOnPickUpListener();
	setOnPickUpListener(*onPickUpListener);
}

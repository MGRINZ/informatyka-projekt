#include "utils.h"

using namespace std;

void fadeIn(Shape &object, int duration, int maxTransparency)
{
	Color color = object.getFillColor();

	fadeIn1<Shape>(object, duration, color, maxTransparency);
	
	object.setFillColor(color);
}

void fadeIn(Sprite &object, int duration, int maxTransparency)
{
	Color color = object.getColor();

	fadeIn1<Sprite>(object, duration, color, maxTransparency);
	
	object.setColor(color);
}
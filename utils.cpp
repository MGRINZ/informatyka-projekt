#include "utils.h"

using namespace std;

int Utils::fadeIn(Shape &object, int duration, int maxTransparency)
{
	Color color = object.getFillColor();

	int status = fadeIn1<Shape>(object, duration, color, maxTransparency);
	
	object.setFillColor(color);
	
	return status;
}

int Utils::fadeIn(Sprite &object, int duration, int maxTransparency)
{
	Color color = object.getColor();

	int status = fadeIn1<Sprite>(object, duration, color, maxTransparency);
	
	object.setColor(color);

	return status;
}
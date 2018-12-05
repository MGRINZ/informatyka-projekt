#include "utils.h"

void fadeIn(Shape &object, int duration, int maxTransparency)
{
	static map<Shape*, Clock*> clockMap;

	Color color = object.getFillColor();
	
	if (color.a >= maxTransparency)
		return;

	Clock *clock;

	if (!clockMap.count(&object))
	{
		clock = new Clock();
		clockMap.insert(pair<Shape*, Clock*>(&object, clock));
	}
	else
		clock = clockMap.at(&object);

	color.a = ( maxTransparency / duration) * clock->getElapsedTime().asMilliseconds();
	
	if (clock->getElapsedTime().asMilliseconds() > duration)
	{
		color.a = maxTransparency;
		clockMap.erase(&object);
	}
	
	object.setFillColor(color);
}

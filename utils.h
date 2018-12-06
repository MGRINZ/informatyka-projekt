#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Utils
{
private:
	template <class T>
	static int fadeIn1(T &object, int duration, Color &color, double maxTransparency = 255)
	{
		static map<T*, Clock*> clockMap;

		if (color.a >= maxTransparency)
			return 1;

		Clock *clock;

		if (!clockMap.count(&object))
		{
			clock = new Clock();
			clockMap.insert(pair<T*, Clock*>(&object, clock));
		}
		else
			clock = clockMap.at(&object);

		color.a = (maxTransparency / duration) * clock->getElapsedTime().asMilliseconds();

		if (clock->getElapsedTime().asMilliseconds() > duration)
		{
			color.a = maxTransparency;
			clockMap.erase(&object);
		}

		return 0;
	}

public:
	static int fadeIn(Shape &object, int duration, int maxTransparency = 255);
	static int fadeIn(Sprite &object, int duration, int maxTransparency = 255);
};
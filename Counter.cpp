#include "Counter.h"
#include <iostream>
#include <sstream>

using namespace std;

void Counter::update()
{
	stringstream ss;
	ss << current;
	setString(ss.str());
}

Counter::Counter() : Counter(0, 0)
{

}

Counter::Counter(int max, int current)
{
	font.loadFromFile("resources/fonts/verdana.ttf");
	setFont(font);
	setFillColor(Color::White);
	setOutlineColor(Color::Black);
	setOutlineThickness(1);

	set(max, current);
	reset();
}

void Counter::set(int max)
{
	this->max = max;
}

void Counter::set(int max, int current)
{
	this->current = current;
	this->max = max;
}

void Counter::reset()
{
	current = 0;
	update();
}

void Counter::count(int duration)
{
	if (current == max)
		return;

	if (animationClock == NULL)
		animationClock = new Clock();

	current = (double) max / duration * animationClock->getElapsedTime().asMilliseconds();
	update();

	if (current >= max)
	{
		current = max;
		update();
		delete animationClock;
		animationClock = NULL;
	}
}

int Counter::getCurrent()
{
	return current;
}

int Counter::getMax()
{
	return max;
}


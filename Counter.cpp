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

Counter::Counter(int end, int start)
{
	font.loadFromFile("resources/fonts/verdana.ttf");
	setFont(font);
	setFillColor(Color::White);
	setOutlineColor(Color::Black);
	setOutlineThickness(1);

	set(end, start);
	reset();
}

void Counter::set(int end)
{
	set(end, 0);
}

void Counter::set(int end, int start)
{
	this->start = start;
	this->end = end;
}

void Counter::reset()
{
	current = 0;
	update();
}

void Counter::count(int duration)
{
	if (current == end)
		return;

	if (animationClock == NULL)
		animationClock = new Clock();

	int elapsedTime = animationClock->getElapsedTime().asMilliseconds();

	current = start + (double)(end - start) / duration * elapsedTime;
	update();

	if (elapsedTime >= duration)
	{
		current = end;
		update();
		delete animationClock;
		animationClock = NULL;
	}
}

int Counter::getStart()
{
	return start;
}

int Counter::getEnd()
{
	return end;
}


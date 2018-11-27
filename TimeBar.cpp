#include "TimeBar.h"
#include <sstream>

TimeBar::TimeBar() : HUDBar()
{
	delete items;
	iconTexture.loadFromFile("resources/textures/hud/clock.png");
	icon.setTexture(iconTexture);
}

void TimeBar::setTimeLeft(int timeLeft)
{
	this->timeLeft = timeLeft;

	int s, m, h;

	s = timeLeft % 60;
	timeLeft /= 60;
	m = timeLeft % 60;
	timeLeft /= 60;
	h = timeLeft;

	stringstream ss;

	if (h > 0)
		ss << ((h < 10) ? "0" : "") << h << ":";
	ss << ((m < 10) ? "0" : "") << m << ":";
	ss << ((s < 10) ? "0" : "") << s;

	counter.setString(ss.str());
}
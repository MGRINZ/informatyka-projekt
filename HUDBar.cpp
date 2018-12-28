#include "HUDBar.h"
#include "utils.h"
#include <sstream>

HUDBar::HUDBar()
{
	this->icon.setTextureRect(IntRect(0, 0, 48, 48));

	counterFont.loadFromFile("resources/fonts/verdana.ttf");
	counter.setFont(counterFont);
	counter.setOutlineColor(Color::Black);
	counter.setOutlineThickness(1);
}

void HUDBar::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(icon);
	target.draw(counter);
}

void HUDBar::setPosition(Vector2f position)
{
	icon.setPosition(position);
	counter.setPosition(Vector2f(position.x + 60, position.y + 4));
}

void HUDBar::move(Vector2f position)
{
	icon.move(position);
	counter.move(position);
}

void HUDBar::setItems(int currentItems, int maxItems)
{
	this->currentItems = currentItems;
	this->maxItems = maxItems;
	stringstream ss;
	ss << currentItems << "/" << maxItems;
	counter.setString(ss.str());
}

int HUDBar::getMaxItems()
{
	return maxItems;
}

int HUDBar::getCurrentItems()
{
	return currentItems;
}

bool HUDBar::fadeIn(int duration)
{
	bool status = false;
	Utils::fadeIn(icon, duration);
	Utils::fadeIn(counter, duration);
	return status;
}

void HUDBar::hide()
{
	icon.setColor(Color(255, 255, 255, 0));
	
	Color counterColor = counter.getFillColor();
	Color counterOutlineColor = counter.getOutlineColor();
	counterColor.a = 0;
	counterOutlineColor.a = 0;

	counter.setFillColor(counterColor);
	counter.setOutlineColor(counterOutlineColor);
}
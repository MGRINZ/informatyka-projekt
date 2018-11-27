#include "HUDBar.h"

HUDBar::HUDBar()
{
	this->icon.setTextureRect(IntRect(0, 0, 48, 48));

	counterFont.loadFromFile("resources/fonts/verdana.ttf");
	counter.setFont(counterFont);
	counter.setOutlineColor(Color::Black);
	counter.setOutlineThickness(1);
}

void HUDBar::draw(RenderWindow & window)
{
	window.draw(icon);
	window.draw(counter);
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
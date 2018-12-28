#include "Menu.h"

Menu::Menu()
{
	menuId = "";
	menu.setLayout(ButtonsGroup::VERTICAL);
	menu.setSpacing(Vector2f(0, 10));
}

void Menu::draw(RenderTarget & target, RenderStates states) const
{
	target.draw(menu);
}

void Menu::setPosition(Vector2f position)
{
	if (this->position == position)
		return;

	this->position = position;
	Vector2f ms = menu.getSize();
	menu.setOrigin(Vector2f(ms.x / 2, 0));
	menu.setPosition(position);
}

string Menu::getMenuId()
{
	return menuId;
}

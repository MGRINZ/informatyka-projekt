#include "ButtonsGroup.h"



ButtonsGroup::ButtonsGroup()
{
	setLayout(Layout::HORIZONTAL);
	setPosition(Vector2f(0, 0));
}

void ButtonsGroup::add(Button button)
{
	//(1)..., wi�c wska�niki w Button::buttons b�d� wskazywa�y na stare adresy element�w...
	for (auto &btn : buttons)
	{
		for (int i = 0; i < Button::buttons.size(); i++)
		{
			if (Button::buttons[i] == &btn)
			{
				//...dlatego trzeba je usun��...(2)
				Button::buttons.erase(Button::buttons.begin() + i);
				break;
			}
		}
	}
	
	buttons.push_back(button);	//vector reallocuje pami��, wi�c adresy element�w si� zmieniaj� ...(1)

	//(2)..., by doda� nowe adresy.
	for (auto &btn : buttons)
		Button::buttons.push_back(&btn);

	setPosition(position);
}

void ButtonsGroup::setLayout(Layout layout)
{
	this->layout = layout;
	setPosition(position);
}

void ButtonsGroup::setSpacing(Vector2f spacing)
{
	this->spacing = spacing;
	setPosition(position);
}

void ButtonsGroup::setPosition(Vector2f position)
{
	this->position = position;
	Vector2f bp(position);
	Vector2f bs;
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i].setOrigin(Vector2f(0, 0));
		bs = buttons[i].getSize();
		buttons[i].setPositiion(position);
		position.x += bs.x + spacing.x;
	}
}

void ButtonsGroup::draw(RenderTarget & target, RenderStates states) const
{
	for (auto &button : buttons)
		target.draw(button);
}

#include "ButtonsGroup.h"

ButtonsGroup::ButtonsGroup()
{
	setLayout(Layout::HORIZONTAL);
	setPosition(Vector2f(0, 0));
}

void ButtonsGroup::add(Button button)
{
	//(1)..., wiêc wskaŸniki w Button::buttons bêd¹ wskazywa³y na stare adresy elementów...
	for (auto &btn : buttons)
	{
		for (int i = 0; i < Button::buttons.size(); i++)
		{
			if (Button::buttons[i] == &btn)
			{
				//...dlatego trzeba je usun¹æ...(2)
				Button::buttons.erase(Button::buttons.begin() + i);
				break;
			}
		}
	}
	
	SelectedButtonOnClickListener *sbClickListener = new SelectedButtonOnClickListener(buttons.size(), &onClickListener);
	button.setOnClickListener(*sbClickListener);
	buttons.push_back(button);	//vector reallocuje pamiêæ, wiêc adresy elementów siê zmieniaj¹ ...(1)

	//(2)..., by dodaæ nowe adresy.
	for (auto &btn : buttons)
		Button::buttons.push_back(&btn);

	setPosition(position);
	setOffset(offset);
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
	position.x -= origin.x;
	position.y -= origin.y;
	Vector2f bp(position);
	Vector2f bs;
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i].setOrigin(Vector2f(0, 0));
		bs = buttons[i].getSize();
		buttons[i].setPositiion(position);
		if(layout == Layout::HORIZONTAL)
			position.x += bs.x + spacing.x;
		else
			position.y += bs.y + spacing.y;
	}
}

Vector2f ButtonsGroup::getPosition()
{
	return position;
}

void ButtonsGroup::setOffset(Vector2f offset)
{
	this->offset = offset;
	for (auto &button : buttons)
		button.setOffset(offset);
}

Vector2f ButtonsGroup::getSize()
{
	Vector2f size(0, 0);
	Vector2f bs;
	double max = 0;
	if (layout == Layout::HORIZONTAL)
	{
		for (auto &button : buttons)
		{
			bs = button.getSize();
			size.x += bs.x + spacing.x;
			if(bs.y > max)
				max = bs.y;
		}
		size.x -= spacing.x;
		size.y = max;
	}
	else
	{
		for (auto &button : buttons)
		{
			bs = button.getSize();
			size.y += bs.y + spacing.y;
			if (bs.x > max)
				max = bs.x;
		}
		size.y -= spacing.y;
		size.x = max;
	}
	return size;
}

void ButtonsGroup::setOrigin(Vector2f origin)
{
	this->origin = origin;
	setPosition(position);
}

void ButtonsGroup::draw(RenderTarget & target, RenderStates states) const
{
	for (auto &button : buttons)
		target.draw(button);
}

void ButtonsGroup::setOnClickListener(ButtonsGroupOnClickListener & onClickListener)
{
	if (this->onClickListener != NULL && &onClickListener != this->onClickListener)
		delete this->onClickListener;
	this->onClickListener = &onClickListener;
}

ButtonsGroup::SelectedButtonOnClickListener::SelectedButtonOnClickListener(int index, ButtonsGroupOnClickListener **onClickListener)
{
	this->index = index;
	this->onClickListener = onClickListener;
}

void ButtonsGroup::SelectedButtonOnClickListener::onClick()
{
	if (*onClickListener != NULL)
		(*onClickListener)->onClick(index);
}
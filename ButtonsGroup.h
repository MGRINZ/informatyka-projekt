#pragma once
#include "Button.h"
#include "ButtonOnClickListener.h"
#include "ButtonsGroupOnClickListener.h"

using namespace std;

class ButtonsGroup : public Drawable
{
private:
	vector<Button> buttons;
	Vector2f spacing;
	Vector2f position;
	int layout;
	enum Layout
	{
		HORIZONTAL,
		VERTICAL
	};
	class SelectedButtonOnClickListener;
	ButtonsGroupOnClickListener *onClickListener;
public:
	ButtonsGroup();
	void add(Button button);
	void setLayout(Layout layout);
	void setSpacing(Vector2f spacing);
	void setPosition(Vector2f position);
	void draw(RenderTarget& target, RenderStates states) const;
	void setOnClickListener(ButtonsGroupOnClickListener &onClickListener);
};

class ButtonsGroup::SelectedButtonOnClickListener : public ButtonOnClickListener
{
private:
	int index;
	ButtonsGroupOnClickListener **onClickListener;
public:
	SelectedButtonOnClickListener(int index, ButtonsGroupOnClickListener **onClickListener);
	void onClick();
};
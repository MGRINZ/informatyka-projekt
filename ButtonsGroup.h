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
	Vector2f origin;
	Vector2f offset;
	int layout;
	class SelectedButtonOnClickListener;
	ButtonsGroupOnClickListener *onClickListener;
public:
	enum Layout
	{
		HORIZONTAL,
		VERTICAL
	};
	ButtonsGroup();
	void add(Button button);
	void setLayout(Layout layout);
	void setSpacing(Vector2f spacing);
	void setPosition(Vector2f position);
	Vector2f getPosition();
	void setOffset(Vector2f offset);
	Vector2f getSize();
	void setOrigin(Vector2f origin);
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
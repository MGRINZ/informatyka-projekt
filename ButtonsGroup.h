#pragma once
#include "Button.h"

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
public:
	ButtonsGroup();
	void add(Button &button);
	void setLayout(Layout layout);
	void setSpacing(Vector2f spacing);
	void setPosition(Vector2f position);
	void draw(RenderTarget& target, RenderStates states) const;
};
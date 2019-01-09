#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Frame : public Drawable
{
private:
	Vector2f position;
	Vector2f size;
	Sprite corners[4];
	Sprite edges[4];
	Sprite container;
	Texture cornersTextures[4];
	Texture edgesTextures[4];
	Clock *animationClock;
	bool shownUp = false;
public:
	Frame();
	~Frame();
	void draw(RenderTarget& target, RenderStates states) const override;
	void setPosition(Vector2f position);
	Vector2f getPosition();
	void setSize(Vector2f size);
	Vector2f getSize();
	Sprite* getContainer();
	void showUp(int duration = 250);
	void show();
	bool isShownUp();
};


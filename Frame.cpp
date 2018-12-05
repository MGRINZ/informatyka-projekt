#include "Frame.h"
#include "utils.h"

Frame::Frame()
{
	cornersTextures[0].loadFromFile("resources/textures/frame/frame_01.png");
	cornersTextures[1].loadFromFile("resources/textures/frame/frame_03.png");
	cornersTextures[2].loadFromFile("resources/textures/frame/frame_09.png");
	cornersTextures[3].loadFromFile("resources/textures/frame/frame_07.png");
	edgesTextures[0].loadFromFile("resources/textures/frame/frame_2.png");
	edgesTextures[1].loadFromFile("resources/textures/frame/frame_6.png");
	edgesTextures[2].loadFromFile("resources/textures/frame/frame_4.png");
	edgesTextures[3].loadFromFile("resources/textures/frame/frame_8.png");

	corners[0].setOrigin(Vector2f(20, 20));
	corners[1].setOrigin(Vector2f(0, 20));
	corners[2].setOrigin(Vector2f(0, 0));
	corners[3].setOrigin(Vector2f(20, 0));

	for (int i = 0; i < 4; i++)
	{
		corners[i].setTexture(&cornersTextures[i]);
		corners[i].setSize(Vector2f(20, 20));
		corners[i].setFillColor(Color(255, 255, 255, 0));
		edges[i].setTexture(&edgesTextures[i]);
	}
}

void Frame::draw(RenderWindow & window)
{
	for(int i = 0; i < 4; i++)
	{
		fadeIn(corners[i], 100);
		//fadeIn<RectangleShape>(corners[i], 5000, animationClock);
		window.draw(corners[i]);
		window.draw(edges[i]);
	}
}

void Frame::setPosition(Vector2f position)
{
	this->position = position;

	for (int i = 0; i < 4; i++)
	{
		corners[i].setPosition(position);
	}
}

Vector2f Frame::getPosition()
{
	return position;
}
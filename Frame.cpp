#include "Frame.h"
#include "utils.h"
#include "Game.h"

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

	size = Vector2f(Game::WIDTH * 0.8, Game::HEIGHT * 0.5); //??? Czy tak zostanie
}

void Frame::showUp()
{
	if (shownUp)
		return;

	int fadedIn = 0;
	for (int i = 0; i < 4; i++)
		fadedIn = Utils::fadeIn(corners[i], 100);

	if (!fadedIn)
		return;

	if (animationClock == NULL)
		animationClock = new Clock();
	int elapsedTime = animationClock->getElapsedTime().asMilliseconds();

	if (elapsedTime <= 5000)
	{
		for (int i = 0; i < 4; i++)
		{
			Vector2f cp = corners[i].getPosition();

			if (i == 0 || i == 3)
				cp.x = position.x -(size.x / 2) / 5000 * elapsedTime; //(size.x / 2) / duration * elapsedTime
			else
				cp.x = position.x + (size.x / 2) / 5000 * elapsedTime; //(size.x / 2) / duration * elapsedTime
			corners[i].setPosition(Vector2f(cp.x, cp.y));
		}
	}
	else if (elapsedTime > 5000 && elapsedTime <= 10000)
	{
		for (int i = 0; i < 4; i++)
		{
			Vector2f cp = corners[i].getPosition();
			if (i == 0 || i == 1)
				cp.y = position.y -(size.y / 2) / 5000 * (elapsedTime - 5000); //(size.x / 2) / (duration - prevDuration) * elapsedTime
			else
				cp.y = position.y + (size.y / 2) / 5000 * (elapsedTime - 5000); //(size.x / 2) / (duration - prevDuration) * elapsedTime
			corners[i].setPosition(Vector2f(cp.x, cp.y));
		}
	}
	else
	{
		shownUp = true;
		delete animationClock;
	}
}

void Frame::draw(RenderWindow & window)
{
	showUp();
	for(int i = 0; i < 4; i++)
	{
		window.draw(corners[i]);
		window.draw(edges[i]);
	}
}

void Frame::setPosition(Vector2f position)
{
	for (int i = 0; i < 4; i++)
	{
		Vector2f cp = corners[i].getPosition();
		cp.x = position.x + cp.x - this->position.x;
		cp.y = position.y + cp.y - this->position.y;
		corners[i].setPosition(cp);
	}

	this->position = position;
}

Vector2f Frame::getPosition()
{
	return position;
}
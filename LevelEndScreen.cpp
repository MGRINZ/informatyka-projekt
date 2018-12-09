#include "LevelEndScreen.h"
#include "Game.h"
#include "utils.h"

LevelEndScreen::LevelEndScreen()
{
	overlay.setFillColor(Color(0, 0, 0, 0));
	overlay.setSize(Vector2f(Game::WIDTH, Game::HEIGHT));
	
	frame.getContainer()->setTexture(*container.getTexture(), false);

	headerFont.loadFromFile("resources/fonts/verdana.ttf");
	header.setFont(headerFont);

	container.append(header);
	container.setBackground(Color(0, 0, 0, 96));

	setSize(Vector2f(1,1));
	setPosition(Vector2f(0, 0));
}

void LevelEndScreen::draw(RenderWindow & window)
{
	Utils::fadeIn(overlay, 100, 192);
	window.draw(overlay);
	
	container.draw();
	
	frame.showUp();
	window.draw(frame);
}

void LevelEndScreen::setPosition(Vector2f position)
{
	this->position = position;
	overlay.setPosition(Vector2f(position.x - Game::WIDTH / 2, position.y - Game::HEIGHT / 2));
	frame.setPosition(position);
}

void LevelEndScreen::setHeader(string header)
{
	FloatRect gb;
	this->header.setString(header);
	gb = this->header.getGlobalBounds();
	this->header.setOrigin(Vector2f(gb.width / 2, gb.height / 2));
}

void LevelEndScreen::setSize(Vector2f size)
{
	frame.setSize(size);
	container.setSize(size);
	header.setPosition(Vector2f(container.getSize().x / 2, 40));
}

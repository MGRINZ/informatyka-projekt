#include "LevelEndScreen.h"
#include "Game.h"
#include "utils.h"

LevelEndScreen::LevelEndScreen()
{
	overlay.setFillColor(Color(0, 0, 0, 0));
	overlay.setSize(Vector2f(Game::WIDTH, Game::HEIGHT));
	
	container.create(Game::WIDTH * 0.8, Game::HEIGHT * 0.5);

	headerFont.loadFromFile("resources/fonts/verdana.ttf");
	header.setFont(headerFont);
	header.setPosition(Vector2f(container.getSize().x / 2, 40));

	frame.setSize(Vector2f(Game::WIDTH * 0.8, Game::HEIGHT * 0.5));
	frame.getContainer()->setTexture(container.getTexture(), false);

	setPosition(Vector2f(0, 0));
}

void LevelEndScreen::draw(RenderWindow & window)
{
	Utils::fadeIn(overlay, 100, 192);
	window.draw(overlay);

	container.clear(Color::Red);
	container.draw(header);
	container.display();
	
	frame.draw(window);
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

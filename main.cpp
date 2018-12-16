#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Level.h"

#include "Button.h"	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include "ButtonsGroup.h"	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include "ButtonOnClickListener.h"	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include "ButtonsGroupOnClickListener.h"	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

using namespace std;
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(Game::WIDTH, Game::HEIGHT), "Gra");
	window.setFramerateLimit(60);
	
	Level level;
	level.load("level3.lvl");

	Button btn(Vector2f(100, 50), "Text");
	Button btn2(Vector2f(101, 50), "Dsa");
	Button btn3(Vector2f(102, 50), "Qwe");
	btn.setPositiion(Vector2f(400, 300));
	btn2.setPositiion(Vector2f(400, 400));
	btn3.setPositiion(Vector2f(400, 500));
	//btn.setOrigin(Vector2f(50, 25));
	btn2.setOrigin(Vector2f(50, 25));
	ButtonsGroup btngrp;
	class a : public ButtonsGroupOnClickListener
	{
	public:
		void onClick(int index)
		{
			cout << index << endl;
		}
	};
	a A;
	btngrp.add(btn);
	btngrp.add(btn2);
	btngrp.add(btn3);
	btngrp.setOnClickListener(A);
	btngrp.setSpacing(Vector2f(10, 20));
	btngrp.setPosition(Vector2f(400, 300));

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		for (auto &button : Button::buttons)
			button->handleEvents(window, &level.getView());

		window.clear();

		switch (level.getStatus())
		{
			case Level::Status::FINISHED:
			case Level::Status::FAILED:
			{
				break;
			}
			default:
			{
				level.handleEntities();
				level.handleItems();
				window.setView(level.getView());
			}
		}

		level.handleFinish();
		level.handleTimers();

		level.draw(window);
		window.draw(btngrp);
		//window.draw(btn);
		//window.draw(btn2);
		window.display();
	}
	return 0;
}
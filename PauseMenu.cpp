#include "PauseMenu.h"
#include "Game.h"

PauseMenu::PauseMenu()
{
	setSize(Vector2f(Game::WIDTH * 0.5 , Game::HEIGHT * 0.6));
	setPosition(Game::getInstance().getLevel().getView().getCenter());
	setHeader("Pauza");

	Button continueButton(Vector2f(300, 50), "Kontynuuj");
	Button restartButton(Vector2f(300, 50), "Restart");
	Button helpButton(Vector2f(300, 50), "Pomoc");
	Button mainMenuButton(Vector2f(300, 50), "Wyjscie do menu");

	menu.setLayout(menu.VERTICAL);
	menu.setSpacing(Vector2f(0, 20));
	menu.setPosition(Vector2f(container.getSize().x / 2, 70));

	menu.add(continueButton);
	menu.add(restartButton);
	menu.add(helpButton);
	menu.add(mainMenuButton);

	Vector2f ms = menu.getSize();
	menu.setOrigin(Vector2f(ms.x / 2, 0));	

	menu.setOnClickListener(onClickListener);
}


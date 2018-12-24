#include "MainMenu.h"

MainMenu::MainMenu(GameMenu &gameMenu) : Menu()
{
	Button newGameButton(Vector2f(300, 50), "Nowa gra");
	Button loadGameButton(Vector2f(300, 50), "Wczytaj gre");
	Button helpButton(Vector2f(300, 50), "Pomoc");
	Button exitButton(Vector2f(300, 50), "Wyjdz");

	menu.add(newGameButton);
	menu.add(loadGameButton);
	menu.add(helpButton);
	menu.add(exitButton);
	
	onClickListener = new MainMenuOnClickListener(gameMenu);

	menu.setOnClickListener(*onClickListener);
}
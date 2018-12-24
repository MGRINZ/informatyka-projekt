#include "NewGameMenu.h"
#include "NewGameMenuOnClickListener.h"
#include <sstream>

NewGameMenu::NewGameMenu(GameMenu & gameMenu)
{
	Button *slots[3];
	for (int i = 0; i < 3; i++)
	{
		stringstream ss;
		ss << "Miejsce zapisu " << i << ".";
		slots[i] = new Button(Vector2f(300, 50), ss.str());
		menu.add(*slots[i]);
	}
	Button backButton(Vector2f(300, 50), "Powrot");
	menu.add(backButton);

	onClickListener = new NewGameMenuOnClickListener(gameMenu);

	menu.setOnClickListener(*onClickListener);
}

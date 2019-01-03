#include "NewGameMenu.h"
#include "NewGameMenuOnClickListener.h"
#include "Save.h"
#include <sstream>

NewGameMenu::NewGameMenu(GameMenu & gameMenu)
{
	Button *slots[3];
	for (int i = 0; i < 3; i++)
	{
		stringstream ss;

		Save save;
		save.setSlot(i);

		if (save.exists())
		{
			save.read();
			ss << "Poziom " << save.getLevel() << ". - " << gameMenu.difficultyNames[save.getDifficulty()];
		}
		else
			ss << "Miejsce zapisu " << (i + 1) << ".";
		
		slots[i] = new Button(Vector2f(300, 50), ss.str());
		menu.add(*slots[i]);
		delete slots[i];
	}
	Button backButton(Vector2f(300, 50), "Powrot");
	menu.add(backButton);

	onClickListener = new NewGameMenuOnClickListener(gameMenu);

	menu.setOnClickListener(*onClickListener);
}

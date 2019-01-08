#include "LoadLevelMenu.h"
#include "Utils.h"
#include <sstream>
#include "Game.h"
#include "Save.h"
#include "LoadLevelMenuOnClickListener.h"

LoadLevelMenu::LoadLevelMenu(GameMenu &gameMenu)
{
	Save save = Game::getInstance().getSave();
	for (int i = 0; i < 5; i++)
	{
		stringstream levelName;
		string levelPath = "resources/levels/";
		stringstream ss;
		levelName << "level" << i + 1 << ".lvl";
		
		if (!Utils::fexists(levelPath + levelName.str()))
			break;

		ss << "Poziom " << i + 1 << ".";

		if (i < save.getLevel())
			ss << " - Wynik: " << save.getHighScore(i);

		Button levelButton(Vector2f(300, 50), ss.str());

		if (i >= save.getLevel())
			levelButton.disable();

		menu.add(levelButton);
	}

	Button backButton(Vector2f(300, 50), "Powrot");
	menu.add(backButton);

	onClickListener = new LoadLevelMenuOnClickListener(gameMenu);

	menu.setOnClickListener(*onClickListener);
}
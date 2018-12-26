#include "NewGameDifficultyMenu.h"
#include "NewGameDifficultyMenuOnClickListener.h"

NewGameDifficultyMenu::NewGameDifficultyMenu(GameMenu &gameMenu)
{
	for (int i = 0; i < 3; i++)
	{
		Button difficultyButton(Vector2f(300, 50), gameMenu.difficultyNames[i]);
		menu.add(difficultyButton);
	}

	Button backButton(Vector2f(300, 50), "Powrot");
	menu.add(backButton);

	onClickListener = new NewGameDifficultyMenuOnClickListener(gameMenu);

	menu.setOnClickListener(*onClickListener);
}

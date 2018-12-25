#include "NewGameDifficultyMenu.h"
#include "NewGameDifficultyMenuOnClickListener.h"

NewGameDifficultyMenu::NewGameDifficultyMenu(GameMenu &gameMenu)
{
	Button easyButton(Vector2f(300, 50), "Ijzi");
	Button mediumButton(Vector2f(300, 50), "Midjum");
	Button hardButton(Vector2f(300, 50), "Hard");
	Button backButton(Vector2f(300, 50), "Powrot");

	menu.add(easyButton);
	menu.add(mediumButton);
	menu.add(hardButton);
	menu.add(backButton);

	onClickListener = new NewGameDifficultyMenuOnClickListener(gameMenu);

	menu.setOnClickListener(*onClickListener);
}

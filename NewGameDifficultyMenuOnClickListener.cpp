#include "NewGameDifficultyMenuOnClickListener.h"
#include "Game.h"

NewGameDifficultyMenuOnClickListener::NewGameDifficultyMenuOnClickListener(GameMenu &gameMenu)
{
	this->gameMenu = &gameMenu;
}

void NewGameDifficultyMenuOnClickListener::onClick(int index)
{
	switch (index)
	{
		case NewGameDifficultyMenuOnClickListener::EASY:
		case NewGameDifficultyMenuOnClickListener::NORMAL:
		case NewGameDifficultyMenuOnClickListener::HARD:
		{
			Game *game = &Game::getInstance();
			Save save = game->getSave();
			save.setDifficulty(index);
			game->loadSave(save);
			save.write();
			game->startLevel(1);
			break;
		}
		case NewGameDifficultyMenuOnClickListener::BACK:
		{
			gameMenu->setStatus(gameMenu->NEW_GAME_MENU);
			break;
		}
	}
}

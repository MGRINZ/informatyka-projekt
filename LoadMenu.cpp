#include "LoadMenu.h"
#include "LoadMenuOnClickListener.h"

LoadMenu::LoadMenu(GameMenu &gameMenu) : NewGameMenu(gameMenu)
{
	onClickListener = new LoadMenuOnClickListener(gameMenu);
	menu.setOnClickListener(*onClickListener);
}

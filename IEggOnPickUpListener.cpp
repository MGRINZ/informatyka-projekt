#include "IEggOnPickUpListener.h"
#include "Game.h"
#include "ItemsBar.h"

void IEggOnPickUpListener::onPickUp(Item & item)
{
	item.disable();
	ItemsBar *itemsBar = Game::getInstance().getLevel().getPlayer().getHUD()->getItemsBar();
	itemsBar->setItems(itemsBar->getCurrentItems() + 1, itemsBar->getMaxItems());
}
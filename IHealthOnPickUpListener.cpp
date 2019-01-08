#include "IHealthOnPickUpListener.h"
#include "Game.h"
#include "Player.h"

void IHealthOnPickUpListener::onPickUp(Item & item)
{
	Player &player = Game::getInstance().getLevel().getPlayer();
	int health = player.getHealth();
	if (health == player.getHUD()->getHealthBar()->getMaxHealth())
		return;

	item.disable();
	player.setHealth(health + 1);
}

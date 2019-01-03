#pragma once

#include "Entity.h"
#include "HUD.h"
#include "Item.h"

class Player : public Entity
{
private:
	HUD hud;
	int health;
	int immunityTimer;
public:
	Player();
	HUD* getHUD();
	void handleMovement(BlocksVector &solidBlocks, View &view, Sprite &background);
	void takingItem(Item &item);
	bool takingDamage(Entity &enemy);
	void dealDamage(Entity &enemy);
	void setHealth(int health);
	int getHealth();
	void reset();
	void immunity();
	void animate();
};
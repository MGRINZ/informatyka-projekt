#pragma once
#include "Entity.h"
#include "Projectile.h"

class EShootingJelly : public Entity
{
private:
	Projectile *projectile;
	Clock *delayClock;
	int shootDelay = 1000;
public:
	EShootingJelly();
	void handleMovement(BlocksVector &solidBlocks);
};


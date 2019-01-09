#pragma once
#include "Entity.h"
#include "Projectile.h"

class EShootingJelly : public Entity
{
protected:
	Projectile *projectile;
	Clock *delayClock;
	int shootDelay = 1000;
public:
	EShootingJelly();
	~EShootingJelly();
	void handleMovement(BlocksVector &solidBlocks);
};


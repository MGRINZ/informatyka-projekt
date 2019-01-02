#pragma once
#include "Entity.h"
#include "Projectile.h"

class EShootingJelly : public Entity
{
private:
	Projectile *projectile;
public:
	EShootingJelly();
	void handleMovement(BlocksVector &solidBlocks);
};


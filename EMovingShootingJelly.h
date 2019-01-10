#pragma once
#include "EShootingJelly.h"
#include "Projectile.h"

class EMovingShootingJelly : public EShootingJelly
{
public:
	EMovingShootingJelly();
	void handleMovement(BlocksVector &solidBlocks);
};


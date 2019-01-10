#pragma once
#include "Entity.h"

class ESleepingJelly : public Entity
{
public:
	ESleepingJelly();
	void handleMovement(BlocksVector &solidBlocks);
};


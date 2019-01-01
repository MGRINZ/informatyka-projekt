#pragma once
#include "Entity.h"

class EJumpJelly : public Entity
{
public:
	EJumpJelly();
	void handleMovement(BlocksVector &solidBlocks);
};


#include "EJumpJelly.h"

EJumpJelly::EJumpJelly() : Entity::Entity("jelly2.png")
{
	animationStep = 100;
}

void EJumpJelly::handleMovement(BlocksVector & solidBlocks)
{
	if (!isAlive())
		return;

	jump(0.10);
	Entity::handleMovement(solidBlocks);
}
#include "EJumpJelly.h"

EJumpJelly::EJumpJelly()
{
	setTexture("jelly2.png");
	animationStep = 100;
}

void EJumpJelly::handleMovement(BlocksVector & solidBlocks)
{
	if (!isActive())
		return;

	if (!isAlive())
		return;

	jump(0.10);
	Entity::handleMovement(solidBlocks);
}
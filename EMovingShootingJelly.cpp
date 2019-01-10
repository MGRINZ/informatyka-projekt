#include "EMovingShootingJelly.h"
#include "Game.h"

EMovingShootingJelly::EMovingShootingJelly() : EShootingJelly::EShootingJelly()
{
	setTexture("jelly3.png");
	animationStep = 100;
	projectile->setTexture("projectile3.png");
}

void EMovingShootingJelly::handleMovement(BlocksVector & solidBlocks)
{
	Entity::handleMovement(solidBlocks);
	EShootingJelly::handleMovement(solidBlocks);
}


#include "ESleepingJelly.h"



ESleepingJelly::ESleepingJelly()
{
	setTexture("jelly5.png");
	animationStep = 200;
	setMovingDirectionX(-1);
	setTextureRect(IntRect(0, 32, 32, 32));
}

void ESleepingJelly::handleMovement(BlocksVector & solidBlocks)
{
	
}


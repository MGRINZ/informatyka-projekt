#include "Projectile.h"
#include <iostream>

const double Projectile::WIDTH = 16;

Projectile::Projectile(string texture) : Entity::Entity(texture)
{
	immortal = true;
	setTextureRect(IntRect(0, WIDTH, WIDTH, WIDTH));
	setOrigin(Vector2f(WIDTH / 2, WIDTH / 2));
}

void Projectile::setTrajectory(double (*f)(double, Vector2f, Vector2f), Vector2f start, Vector2f end)
{
	trajectoryFunction = f;
	trajectoryStart = start;
	trajectoryEnd = end;
}

void Projectile::shoot(BlocksVector & solidBlocks)
{
	if (!isActive())
		return;

	if (trajectoryFunction == NULL)
		return;
	
	Vector2f currentPosition = getPosition();
	Vector2f newPosition = currentPosition;
	Vector2f dposition;
	
	double x = 0.001;

	while (true)
	{
		newPosition.x += getMovingDirectionX() * x;
		newPosition.y = trajectoryFunction(newPosition.x, trajectoryStart, trajectoryEnd);
		dposition.x = newPosition.x - currentPosition.x;
		dposition.y = newPosition.y - currentPosition.y;
		if (sqrt(dposition.x * dposition.x + dposition.y * dposition.y) > 4)
			break;
		x += 0.001;
	}

	Sprite::setPosition(newPosition);

	if (getMovingDirectionX() == -1)
	{
		if (!canGoLeft(solidBlocks))
			deactivate();
	}
	else
	{
		if (!canGoRight(solidBlocks))
			deactivate();
	}
}

#include "Projectile.h"
#include "Game.h"
#include <iostream>

Projectile::Projectile(string texture)
{
	WIDTH = 16;
	setTexture(texture);
	immortal = true;
	setTextureRect(IntRect(0, WIDTH, WIDTH, WIDTH));
	setOrigin(Vector2f(WIDTH / 2, WIDTH / 2));
	animationStep = 50;
}

void Projectile::setTrajectory(double (*f)(double, Vector2f, Vector2f), Vector2f start, Vector2f end)
{
	trajectoryFunction = f;
	trajectoryStart = start;
	trajectoryEnd = end;
}

void Projectile::shoot(BlocksVector & blocks)
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

	dposition.x = newPosition.x - trajectoryStart.x;
	dposition.y = newPosition.y - trajectoryStart.y;

	if (sqrt(dposition.x * dposition.x + dposition.y * dposition.y) > Game::WIDTH)
		deactivate();

	Sprite::setPosition(newPosition);

	if (getMovingDirectionX() == -1)
	{
		if (!canGoLeft(blocks))
			deactivate();
	}
	else
	{
		if (!canGoRight(blocks))
			deactivate();
	}

	if (dposition.y > 0)
	{
		if (!canGoDown(blocks))
			deactivate();
	}
	else
	{
		if (!canGoUp(blocks))
			deactivate();
	}

}

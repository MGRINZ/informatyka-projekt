#include "Projectile.h"
#include <iostream>

Projectile::Projectile(string texture) : Entity::Entity(texture)
{
	immortal = true;
}

void Projectile::setTrajectory(double (*f)(double, Vector2f, Vector2f), Vector2f start, Vector2f end)
{
	trajectoryFunction = f;
	trajectoryStart = start;
	trajectoryStart = end;
}

void Projectile::shoot()
{
	if (trajectoryFunction == NULL)
		return;
	std::cout << trajectoryFunction(trajectoryStart.x, trajectoryStart, trajectoryEnd) << std::endl;
}

#pragma once
#include "Entity.h"

class Projectile : public Entity
{
private:
	double (*trajectoryFunction)(double, Vector2f, Vector2f);
	Vector2f trajectoryStart;
	Vector2f trajectoryEnd;
public:
	const static double WIDTH;
	Projectile(string texture);
	void setTrajectory(double (*f)(double, Vector2f, Vector2f), Vector2f start, Vector2f end);
	void shoot(BlocksVector & solidBlocks);
};


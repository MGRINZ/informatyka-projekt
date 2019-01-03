#include "EShootingJelly.h"
#include "Game.h"

EShootingJelly::EShootingJelly() : Entity::Entity("jelly4.png")
{
	animationStep = 100;
	projectile = new Projectile("");
	Game::getInstance().getLevel().addProjectile(projectile);
}

void EShootingJelly::handleMovement(BlocksVector & solidBlocks)
{
	if (!isActive())
		return;

	if (!isAlive())
		return;

	Vector2f pp = Game::getInstance().getLevel().getPlayer().getPosition();
	Vector2f ep = getPosition();

	if (pp.x < ep.x)
		setMovingDirectionX(-1);
	else
		setMovingDirectionX(1);

	if (!projectile->isActive())
	{
		if(delayClock == NULL)
			delayClock = new Clock();

		if (delayClock->getElapsedTime().asMilliseconds() < shootDelay)
			return;

		projectile->Sprite::setPosition(ep);
		projectile->setTrajectory([](double x, Vector2f start, Vector2f end) -> double {
			double a = (start.y - end.y) / (start.x - end.x);
			return a * (x - start.x) + start.y;
		}, ep, pp);
		projectile->setMovingDirectionX(getMovingDirectionX());
		projectile->activate();
	}
	else
	{
		delete delayClock;
		delayClock = NULL;
	}
}



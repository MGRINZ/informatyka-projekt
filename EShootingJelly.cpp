#include "EShootingJelly.h"
#include "Game.h"

EShootingJelly::EShootingJelly()
{
	setTexture("jelly4.png");
	animationStep = 100;
	projectile = new Projectile("projectile4.png");
	Game::getInstance().getLevel().addProjectile(projectile);
}

EShootingJelly::~EShootingJelly()
{
	delete projectile;
	if(delayClock != NULL)
		delete delayClock;
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

		ep.x += getMovingDirectionX() * WIDTH / 2;
		ep.y -= WIDTH / 2;
		pp.y -= Game::getInstance().getLevel().getPlayer().getWidth() / 2;

		projectile->Sprite::setPosition(ep);
		projectile->setTrajectory([](double x, Vector2f start, Vector2f end) -> double {
			double an = start.y - end.y;
			double ad = start.x - end.x;

			if (ad == 0)
				ad = 0.000000001;

			double a = an / ad;

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



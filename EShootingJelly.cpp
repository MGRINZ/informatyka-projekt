#include "EShootingJelly.h"
#include "Game.h"

EShootingJelly::EShootingJelly() : Entity::Entity("jelly4.png")
{
	animationStep = 100;
	projectile = new Projectile("");
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
		projectile->Sprite::setPosition(ep);
		projectile->setTrajectory([] (double x, Vector2f start, Vector2f end) -> double {
			double a = (start.y - end.y) / (start.x - end.x);
			cout << a << endl;
			return a * (x - start.x) + start.y;
		}, ep, pp);
		projectile->activate();
	}
	else
	{
		projectile->shoot();
	}

}



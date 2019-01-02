#include "Game.h"
#include "Player.h"

void Player::handleMovement(BlocksVector &solidBlocks, View &view, Sprite &background)
{
	if (!isActive())
		return;

	Vector2f velocity(0, 0);
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		if (canGoRight(solidBlocks))
		{
			velocity = Vector2f(Block::WIDTH / 8, 0);
			setMovingDirectionX(1);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		if (canGoLeft(solidBlocks))
		{
			velocity = Vector2f(-Block::WIDTH / 8, 0);
			setMovingDirectionX(-1);
		}
	}

	move(velocity);
	if ((getMovingDirectionX() == 1 && getPosition().x > view.getCenter().x + Game::WIDTH / 2 - Game::WIDTH * 0.2) || (getMovingDirectionX() == -1 && getPosition().x < view.getCenter().x - Game::WIDTH / 2 + Game::WIDTH * 0.2))
	{
		view.move(velocity);
		background.move(velocity);
		hud.move(velocity);
	}

	if (!Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Left))
		setMovingDirectionX(0);
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		jump();
	}
	if (!Keyboard::isKeyPressed(Keyboard::Up))
	{
		setJumping(false);
	}

	cout << (int) (getPosition().x / WIDTH) << ";" << (int) ((getPosition().y - 1) / WIDTH) << endl; //Debug: player position
}

Player::Player() : Entity("easteregg-man.png")
{
	animationStep = 50;
}

HUD * Player::getHUD()
{
	return &hud;
}

void Player::takingItem(Item &item)
{
	FloatRect gb = item.getGlobalBounds();
	if (getGlobalBounds().intersects(gb))
	{
		item.disable();

	}
}

void Player::takingDamage(Entity & enemy)
{
	if (!enemy.isAlive())
		return;

	FloatRect egb = enemy.getGlobalBounds();
	Vector2f ppos = getPosition();
	if (!egb.intersects(getGlobalBounds()))
		return;

	if ((ppos.x >= egb.left && ppos.x <= egb.left + Entity::WIDTH && getMovingDirectionY() == 1))	//TODO: Mo¿e daæ jakieœ 10% szerokoœci?
	{
		dealDamage(enemy);
		return;
	}

	if (immunityTimer)
		return;

	setHealth(getHealth() - 1);
	immunityTimer = 2;
	setColor(Color::Transparent);
}

void Player::dealDamage(Entity & enemy)
{
	enemy.die();
	setJumping(false);
	yVelocityDown = 0;
	jump();
}

void Player::setHealth(int health)
{
	this->health = health;
	hud.getHealthBar()->setHealth(health);
	if (health < 0)
		alive = false;
}

int Player::getHealth()
{
	return health;
}

void Player::reset()
{
	Entity::reset();
	hud.setPosition(Vector2f(50, 20));

	int difficulty = Game::getInstance().getSave().getDifficulty();

	hud.getHealthBar()->setMaxHealth(3 - difficulty);
	setHealth(3 - difficulty);
	immunityTimer = 0;
	setColor(Color::White);
	setTextureRect(IntRect(0, 0, WIDTH, WIDTH));
	activate();
}

void Player::immunity()
{
	if (immunityTimer > 0)
		immunityTimer--;

	if (immunityTimer <= 0)
		setColor(Color::White);
}

void Player::animate()
{
	if (immunityTimer > 0)
	{
		if (animateClock.getElapsedTime().asMilliseconds() % 100 > 0)
			setColor(Color::Transparent);
		if (animateClock.getElapsedTime().asMilliseconds() % 100 > 50)
			setColor(Color::White);
	}
	Entity::animate();
}
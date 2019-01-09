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

	//cout << (int) (getPosition().x / WIDTH) << ";" << (int) ((getPosition().y - 1) / WIDTH) << endl; //Debug: player position
}

Player::Player()
{
	animationStep = 50;
}

HUD * Player::getHUD()
{
	return &hud;
}

void Player::takingItem(Item &item)
{
	if (!item.isActive())
		return;

	FloatRect gb = item.getGlobalBounds();
	if (getGlobalBounds().intersects(gb))
		item.triggerOnPickupEvent();
}

bool Player::takingDamage(Entity & enemy) //Zwraca true jeœli obra¿enia zosta³y zadane, w przeciwnym razie – false
{
	if (!enemy.isActive())
		return false;

	if (!enemy.isAlive())
		return false;

	FloatRect egb = enemy.getGlobalBounds();
	Vector2f ppos = getPosition();
	if (!egb.intersects(getGlobalBounds()))
		return false;

	if ((ppos.x >= egb.left && ppos.x <= egb.left + enemy.getWidth() && getMovingDirectionY() == 1))	//TODO: Mo¿e daæ jakieœ 10% szerokoœci?
	{
		if (!enemy.isImmortal())
		{
			dealDamage(enemy);
			return false;
		}
	}

	if (immunityTimer)
		return false;

	setHealth(getHealth() - 1);
	immunityTimer = 2;
	setColor(Color::Transparent);
	return true;
}

void Player::dealDamage(Entity & enemy)
{
	if (enemy.isImmortal())
		return;

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
	setTexture("easteregg-man.png");
	hud.setPosition(Vector2f(50, 20));

	int difficulty = Game::getInstance().getSave().getDifficulty();

	hud.getHealthBar()->setMaxHealth(3 - difficulty);
	hud.getItemsBar()->setItems(0, 0);
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
#include <iostream>
#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace std;
using namespace sf;

const float Block::WIDTH = Game::HEIGHT / 18.75;
const float Entity::WIDTH = Block::WIDTH;
const string Level::LEVEL_PROPERTY_SETTINGS = ";settings";
const string Level::LEVEL_PROPERTY_TERRAIN = ";terrain";
const string Level::LEVEL_PROPERTY_BACKGROUND = ";background";
const string Level::LEVEL_PROPERTY_FOREGROUND = ";foreground";
const string Level::LEVEL_PROPERTY_ITEMS = ";items";
const string Level::LEVEL_PROPERTY_ENTITIES = ";entities";

Level::Level()
{
	addBackgroundBlock(Block(endPosition[0].x, endPosition[0].y));
	addBackgroundBlock(Block(endPosition[1].x, endPosition[1].y));
}

void Level::addSolidBlock(Block block)
{
	solidBlocks.push_back(block);
}

void Level::addBackgroundBlock(Block block)
{
	backgroundBlocks.push_back(block);
}

void Level::addForegroundBlock(Block block)
{
	foregroundBlocks.push_back(block);
}

void Level::addItem(Item item)
{
	items.push_back(item);
}

void Level::addEnemy(Entity * entity)
{
	enemies.push_back(entity);
}

void Level::draw(RenderWindow &window)
{
	window.draw(background);

	for (auto &block : backgroundBlocks)
		window.draw(block);
	for (auto &block : solidBlocks)
		window.draw(block);
	for (auto &item : items)
	{
		if(item.isActive())
			window.draw(item);
	}
	
	window.draw(player);

	for (auto &enemy : enemies)
		window.draw(*enemy);

	for (auto &block : foregroundBlocks)
		window.draw(block);

	player.getHUD()->draw(window);

	if(getStatus() == LEVEL_STATUS_FINISHED)
		endScreen.draw(window);
}

int Level::load(string levelName)
{
	status = LEVEL_STATUS_LOADING;

	solidBlocks.clear();
	backgroundBlocks.clear();
	foregroundBlocks.clear();
	enemies.clear();
	items.clear();
	player.reset();

	ifstream levelInputStream("resources/levels/" + levelName);
	if (!levelInputStream.is_open())
		return LEVEL_LOAD_ERROR_OPEN_FILE;

	string line;
	string property;
	while (getline(levelInputStream, line))
	{
		if (line[0] == ';')
		{
			property = line;
			continue;
		}
		else
		{
			if (property == LEVEL_PROPERTY_SETTINGS)
			{
				int pos = -1;
				if (line.find("name") == 0)
					name = line.substr(5);
				else if (line.find("background") == 0)
				{
					background.setTexture(line.substr(11));
					background.setPosition(Vector2f(0, 0));
				}
				else if (line.find("audio") == 0)
					audio = line.substr(6);
				else if (line.find("start") == 0)
				{
					string startPosition = line.substr(6);
					string x, y;
					stringstream ss;
					ss << startPosition;
					getline(ss, x, ';');
					getline(ss, y, ';');
					player.setPosition(atoi(x.c_str()), atoi(y.c_str()));
				}
				else if (line.find("end") == 0)
				{
					string startPosition = line.substr(4);
					string x, y;
					stringstream ss;
					ss << startPosition;
					getline(ss, x, ';');
					getline(ss, y, ';');
					endPosition[0].x = atoi(x.c_str());
					endPosition[0].y = atoi(y.c_str());
					getline(ss, x, ';');
					getline(ss, y, ';');
					endPosition[1].x = atoi(x.c_str());
					endPosition[1].y = atoi(y.c_str());
				}
				else if (line.find("time") == 0)
				{
					timeLeft = atoi(line.substr(5).c_str());
				}
			}
			else if (property == LEVEL_PROPERTY_TERRAIN || property == LEVEL_PROPERTY_BACKGROUND || property == LEVEL_PROPERTY_FOREGROUND)
			{
				int x, y;
				string texture;
				string token;

				stringstream ss;
				ss << line;
				getline(ss, token, ';');
				x = atoi(token.c_str());
				getline(ss, token, ';');
				y = atoi(token.c_str());
				getline(ss, token, ';');
				texture = token;
				if(property == LEVEL_PROPERTY_TERRAIN)
					addSolidBlock(Block(x, y, texture));
				else if(property == LEVEL_PROPERTY_BACKGROUND)
					addBackgroundBlock(Block(x, y, texture));
				else if(property == LEVEL_PROPERTY_FOREGROUND)
					addForegroundBlock(Block(x, y, texture));

			}
			else if (property == LEVEL_PROPERTY_ITEMS)
			{
				int x, y;
				string type;

				string token;
				stringstream ss;
				ss << line;
				getline(ss, token, ';');
				x = atoi(token.c_str());
				getline(ss, token, ';');
				y = atoi(token.c_str());
				getline(ss, token, ';');
				type = token;
				addItem(Item(x, y, "egg1.png"));
			}
			else if (property == LEVEL_PROPERTY_ENTITIES)
			{
				int x, y;
				string type;
				string flags;

				string token;
				stringstream ss;
				ss << line;
				getline(ss, token, ';');
				x = atoi(token.c_str());
				getline(ss, token, ';');
				y = atoi(token.c_str());
				getline(ss, token, ';');
				type = token;
				getline(ss, token, ';');
				flags = token;

				Entity* enemy = NULL;
				if (type == "jelly")
					enemy = new EJelly();
				enemy->setPosition(x, y);
				
				if (!flags.empty())
				{
					ss.str("");
					ss.clear();
					ss << flags;
					while (!ss.eof())
					{
						getline(ss, token, '|');
						cout << token;
						enemy->setFlag(token, true);
					}
				}

				addEnemy(enemy);
			}
			else
				continue;
		}
	}

	view = View(FloatRect(0, 0, Game::WIDTH, Game::HEIGHT));
	player.getHUD()->getTimeBar()->setTimeLeft(timeLeft);
	status = LEVEL_STATUS_IN_GAME;
	return LEVEL_LOAD_SUCCESS;
}

void Level::handleEntities()
{
	for (auto &enemy : enemies)
	{
		enemy->handleGravity(solidBlocks);
		//enemy->animate();
		enemy->handleMovement(solidBlocks);
		player.takingDamage(*enemy);
	}
	player.handleGravity(solidBlocks);
	player.animate();
	player.handleMovement(solidBlocks, view, background);

	player.getHUD()->getEnemiesBar()->setItems(&enemies);
}

void Level::handleItems()
{
	for (auto &item : items)
	{
		item.animate();
		player.takingItem(item);
	}
	player.getHUD()->getItemsBar()->setItems(&items);
}

void Level::handleFinish()
{
	FloatRect gb = player.getGlobalBounds();
	FloatRect endArea(endPosition[0].x * Block::WIDTH, endPosition[0].y * Block::WIDTH, (endPosition[1].x - endPosition[0].x + 1) * Block::WIDTH, (endPosition[1].y - endPosition[0].y + 1) * Block::WIDTH);
	
	if (!gb.intersects(endArea))
		return;

	setStatus(LEVEL_STATUS_FINISHED);
	endScreen.setPosition(view.getCenter());

	if (Keyboard::isKeyPressed(Keyboard::Enter))
		load("level3.lvl");
}

void Level::handleTimers()
{
	if (levelClock.getElapsedTime().asSeconds() < 1)
		return;

	if (getStatus() == LEVEL_STATUS_IN_GAME)
	{
		if(timeLeft > 0)
			timeLeft--;
		player.getHUD()->getTimeBar()->setTimeLeft(timeLeft);

		player.immunity();
	}

	levelClock.restart();
}

View Level::getView()
{
	return view;
}

int Level::getStatus()
{
	return status;
}

void Level::setStatus(int status)
{
	this->status = status;
}

void Entity::handleGravity(BlocksVector &blocks, float gravity)
{
	Vector2f entityPosition = getPosition();
	float eX = entityPosition.x;
	float eY = entityPosition.y;

	Block *blockDL = blocks.getSolidBlockAtPosition((eX - WIDTH / 2) / Block::WIDTH, (eY - WIDTH + Block::WIDTH) / Block::WIDTH);
	Block *blockDR = blocks.getSolidBlockAtPosition((eX + WIDTH / 2 - 1) / Block::WIDTH, (eY - WIDTH + Block::WIDTH) / Block::WIDTH);
	
	Block *blockUL = blocks.getSolidBlockAtPosition((eX - WIDTH / 2) / Block::WIDTH, (eY - WIDTH + ((yVelocityDown + yVelocityUp) + 0.025) * Block::WIDTH) / Block::WIDTH);
	Block *blockUR = blocks.getSolidBlockAtPosition((eX + WIDTH / 2 - 1) / Block::WIDTH, (eY - WIDTH + ((yVelocityDown + yVelocityUp) + 0.025) * Block::WIDTH) / Block::WIDTH);

	if (blockUL != NULL || blockUR != NULL)
	{
		yVelocityUp = 0.0;
		yVelocityDown = 0.0;
		jumping = false;
		setMovingDirectionY(0);
	}


	if (blockDL != NULL || blockDR != NULL)
	{
		Sprite::setPosition(Vector2f(eX, (int)(eY / Block::WIDTH) * Block::WIDTH));
		yVelocityDown = 0.0;
		yVelocityUp = 0.0;
		setMovingDirectionY(0);
		return;
	}

	if(yVelocityDown == yVelocityUp)
		yVelocityDown = 0.0;

	yVelocityDown += gravity * 0.0017;
	move(Vector2f(0, (yVelocityDown + yVelocityUp) * Block::WIDTH));
	if (yVelocityDown + yVelocityUp > 0)
		setMovingDirectionY(1);
	else if(yVelocityDown + yVelocityUp < 0)
		setMovingDirectionY(-1);
}

bool Entity::canGoRight(BlocksVector &blocks)
{
	Vector2f entityPosition = getPosition();
	float eX = entityPosition.x;
	float eY = entityPosition.y;

	Block *blockU = blocks.getSolidBlockAtPosition((eX - WIDTH / 2 + Block::WIDTH) / Block::WIDTH, (eY - WIDTH) / Block::WIDTH);
	Block *blockD = blocks.getSolidBlockAtPosition((eX - WIDTH / 2 + Block::WIDTH) / Block::WIDTH, (eY - 1) / Block::WIDTH);

	if (getFlag(Flags::SMART))
	{
		Block *blockD2 = blocks.getSolidBlockAtPosition((eX) / Block::WIDTH, (eY + WIDTH) / Block::WIDTH);
		if (blockD2 == NULL && !isMovingY)
			return false;
	}
	if (blockU == NULL && blockD == NULL)
		return true;

	return false;
}

bool Entity::canGoLeft(BlocksVector &blocks)
{
	Vector2f entityPosition = getPosition();
	float eX = entityPosition.x;
	float eY = entityPosition.y;

	Block *blockU = blocks.getSolidBlockAtPosition((eX + WIDTH / 2 - Block::WIDTH - 4) / Block::WIDTH, (eY - WIDTH) / Block::WIDTH);	// - 4 (prêdkoœæ w piks)
	Block *blockD = blocks.getSolidBlockAtPosition((eX + WIDTH / 2 - Block::WIDTH - 4) / Block::WIDTH, (eY - 1) / Block::WIDTH);		// - 4 (prêdkoœæ w piks)

	if (getFlag(Flags::SMART))
	{
		Block *blockD2 = blocks.getSolidBlockAtPosition((eX - 1) / Block::WIDTH, (eY + WIDTH) / Block::WIDTH);
		if (blockD2 == NULL && !isMovingY)
			return false;
	}
	if (blockU == NULL && blockD == NULL)
		return true;

	return false;
}

void Entity::handleMovement(BlocksVector &solidBlocks)
{
	if (!isAlive())
		return;
	if (getMovingDirectionX() == 0)
		setMovingDirectionX(-1);

	Vector2f velocity(0, 0);
	
	if (getMovingDirectionX() == -1)
	{
		if (canGoLeft(solidBlocks))
			velocity = Vector2f(-Block::WIDTH / 32, 0);
		else	
			setMovingDirectionX(1);
	} else if (getMovingDirectionX() == 1)
	{
		if (canGoRight(solidBlocks))
			velocity = Vector2f(Block::WIDTH / 32, 0);
		else
			setMovingDirectionX(-1);
	}

	//move(velocity);
}

void Entity::jump()
{
	if (!isJumping() && yVelocityDown > 0)
		return;
	if (yVelocityUp == 0)
		yVelocityUp = -0.27;
	else if(yVelocityUp > -0.37)
		yVelocityUp -= 10 * 0.001;
	move(Vector2f(0, -0.025 * Block::WIDTH));
	jumping = true;
}

void Entity::setJumping(bool jumping)
{
	this->jumping = jumping;
}

bool Entity::isJumping()
{
	return jumping;
}

Block::Block(int x, int y)
{
	setSize(Vector2f(WIDTH, WIDTH));
	setPosition(x, y);
}

Block::Block(int x, int y, string txt) : Block(x, y)
{
	texture->loadFromFile("resources/textures/blocks/" + txt);
	setTexture(texture);
}

void Block::setPosition(int x, int y)
{
	RectangleShape::setPosition(Vector2f(x * WIDTH, y * WIDTH));
}

Block* BlocksVector::getSolidBlockAtPosition(int x, int y)
{
	for (auto &block : *this)
	{
		Vector2f blockPosition = block.getPosition();
		if (blockPosition.x == x * Block::WIDTH && blockPosition.y == y * Block::WIDTH)
			return &block;
	}
	return nullptr;
}

Background::Background()
{
	
}

void Background::setTexture(String texture)
{
	name = texture;
	if(!texture.isEmpty())
	{
		this->texture.loadFromFile("resources/backgrounds/" + texture);
		Sprite::setTexture(this->texture);
	}
}

void Entity::animate()
{
	Vector2u txtSize = texture.getSize();
	int jumpFrame = (txtSize.x / WIDTH - 1);	//Ostatnia klatka tekstury przeznaczona na animacjê skoku

	if(isMovingY) {	
		IntRect txtRect = getTextureRect();
		txtRect.left = jumpFrame * WIDTH;
		if(isMovingX == 1)
			txtRect.top = 0;
		else if (isMovingX == -1)
			txtRect.top = WIDTH;
		setTextureRect(txtRect);
		return;
	}

	if(!isMovingX) {
		IntRect txtRect = getTextureRect();
		txtRect.left = 0;
		setTextureRect(txtRect);
		return;
	}

	if (animateClock.getElapsedTime().asMilliseconds() >= 50)
	{
		IntRect txtRect = getTextureRect();
		txtRect.left += WIDTH * ((txtRect.left / WIDTH) + 1);
		if (txtRect.left >= (jumpFrame - 1) * WIDTH)
			txtRect.left = 0;
		if (isMovingX == 1)
			txtRect.top = 0;
		else if (isMovingX == -1)
			txtRect.top = WIDTH;
		setTextureRect(txtRect);
		animateClock.restart();
	}
}

void Entity::setMovingDirectionX(int x)
{
	isMovingX = x;
}

void Entity::setMovingDirectionY(int y)
{
	isMovingY = y;
}

int Entity::getMovingDirectionX()
{
	return isMovingX;
}

int Entity::getMovingDirectionY()
{
	return isMovingY;
}

bool Entity::getFlag(Flags flag)
{
	return flags[flag];
}

bool Entity::getFlag(string flag)
{
	return getFlag(getFlagByName(flag));
}

void Entity::setFlag(Flags flag, bool value)
{
	flags[flag] = value;
}

void Entity::setFlag(string flag, bool value)
{
	setFlag(getFlagByName(flag), value);
}

Entity::Flags Entity::getFlagByName(string name)
{
	if (name == "SMART")
		return Flags::SMART;
}

bool Entity::isAlive()
{
	return alive;
}

void Entity::die()
{
	alive = false;
}

Entity::Entity()
{
	setOrigin(Vector2f(WIDTH / 2, WIDTH));
	reset();
}

Entity::Entity(string texture) : Entity()
{
	this->texture.loadFromFile("resources/textures/entities/" + texture);
	setTexture(this->texture);
	setTextureRect(IntRect(0, 0, WIDTH, WIDTH));
}

void Entity::reset()
{
	yVelocityDown = 0.0;
	yVelocityUp = 0.0;
	jumping = false;
	isMovingX = 0;
	isMovingY = 0;
	alive = true;
}

void Entity::setPosition(int x, int y)
{
	Sprite::setPosition(Vector2f(x * WIDTH + WIDTH / 2, y * WIDTH + WIDTH));
}

Item::Item(int x, int y) : Block(x, y)
{

}

Item::Item(int x, int y, string txt) : Block(x, y)
{
	texture->loadFromFile("resources/textures/" + txt);
	setTexture(texture);
	setTextureRect(IntRect(0, 0, WIDTH, WIDTH));
}

bool Item::isActive()
{
	return active;
}

void Item::disable()
{
	active = false;
}

void Item::animate()
{
	Vector2u txtSize = texture->getSize();
	if (animateClock.getElapsedTime().asMilliseconds() >= 100)
	{
		IntRect txtRect = getTextureRect();
		txtRect.left += WIDTH * ((txtRect.left / WIDTH) + 1);
		if (txtRect.left >= txtSize.x)
			txtRect.left = 0;
		setTextureRect(txtRect);
		animateClock.restart();
	}
}

LevelEndScreen::LevelEndScreen()
{
	FloatRect gb;

	overlay.setFillColor(Color(0,0,0,192));
	overlay.setSize(Vector2f(Game::WIDTH, Game::HEIGHT));
	
	container.setFillColor(Color::Blue);
	container.setOrigin(Vector2f(Game::WIDTH * 0.8 / 2, Game::HEIGHT * 0.5 / 2));
	container.setSize(Vector2f(Game::WIDTH * 0.8, Game::HEIGHT * 0.5));
	
	headerFont.loadFromFile("resources/fonts/verdana.ttf");
	
	header.setFont(headerFont);
	header.setString("Poziom ukonczony");
	gb = header.getGlobalBounds();
	header.setOrigin(Vector2f(gb.width / 2, gb.height / 2));

	setPosition(Vector2f(0, 0));
}

void LevelEndScreen::draw(RenderWindow & window)
{
	window.draw(overlay);
	window.draw(container);
	window.draw(header);
}

void LevelEndScreen::setPosition(Vector2f position)
{
	this->position = position;
	overlay.setPosition(Vector2f(position.x - Game::WIDTH / 2, position.y - Game::HEIGHT / 2));
	container.setPosition(Vector2f(position.x, position.y));
	header.setPosition(Vector2f(position.x, position.y - 120));
}

HUD::HUD()
{
	setPosition(Vector2f(50, 20));
}

void HUD::draw(RenderWindow & window)
{
	healthBar.draw(window);
	itemsBar.draw(window);
	enemiesBar.draw(window);
	timeBar.draw(window);
}

void HUD::setPosition(Vector2f position)
{
	healthBar.setPosition(Vector2f(position));
	itemsBar.setPosition(Vector2f(position.x + 200, position.y));
	enemiesBar.setPosition(Vector2f(position.x + 350, position.y));
	timeBar.setPosition(Vector2f(position.x + 500, position.y));
}

void HUD::move(Vector2f position)
{
	healthBar.move(position);
	itemsBar.move(position);
	enemiesBar.move(position);
	timeBar.move(position);
}

HealthBar * HUD::getHealthBar()
{
	return &healthBar;
}

ItemsBar * HUD::getItemsBar()
{
	return &itemsBar;
}

EnemiesBar * HUD::getEnemiesBar()
{
	return &enemiesBar;
}

TimeBar * HUD::getTimeBar()
{
	return &timeBar;
}

HealthBar::HealthBar()
{
	healthTexture.loadFromFile("resources/textures/hud/health.png");
	healthTextureEmpty.loadFromFile("resources/textures/hud/health_empty.png");
	setHealth(3);
}

void HealthBar::draw(RenderWindow & window)
{
	for(int i = 0; i < maxHealth; i++)
		window.draw(health[i]);
}

void HealthBar::setHealth(int hp)
{
	for (int i = 0; i < maxHealth; i++)
	{
		if (i < hp)
			health[i].setTexture(healthTexture);
		else
			health[i].setTexture(healthTextureEmpty);
	}
}

void HealthBar::setMaxHealth(int maxHealth)
{
	this->maxHealth = maxHealth;
}

void HealthBar::setPosition(Vector2f position)
{
	this->position = position;
	for (int i = 0; i < maxHealth; i++)
		health[i].setPosition(Vector2f(position.x + i * 50, position.y));
}

void HealthBar::move(Vector2f position)
{
	this->position.x += position.x;
	this->position.y += position.y;
	for (int i = 0; i < maxHealth; i++)
		health[i].move(position);
}

HUDBar::HUDBar()
{
	this->icon.setTextureRect(IntRect(0, 0, 48, 48));

	counterFont.loadFromFile("resources/fonts/verdana.ttf");
	counter.setFont(counterFont);
	counter.setOutlineColor(Color::Black);
	counter.setOutlineThickness(1);
}

ItemsBar::ItemsBar() : HUDBar()
{
	iconTexture.loadFromFile("resources/textures/hud/egg.png");
	icon.setTexture(iconTexture);
}

void HUDBar::draw(RenderWindow & window)
{
	window.draw(icon);
	window.draw(counter);
}

void HUDBar::setPosition(Vector2f position)
{
	icon.setPosition(position);
	counter.setPosition(Vector2f(position.x + 60, position.y + 4));
}

void HUDBar::move(Vector2f position)
{
	icon.move(position);
	counter.move(position);
}

void ItemsBar::setItems(vector<Item>* items)
{
	this->items = items;
	int count = 0;
	for (auto &item : *items)
	{
		if (!item.isActive())
			count++;
	}

	stringstream ss;
	ss << count << "/" << items->size();
	counter.setString(ss.str());
}

EnemiesBar::EnemiesBar() : HUDBar()
{
	iconTexture.loadFromFile("resources/textures/hud/enemy.png");
	icon.setTexture(iconTexture);
}

void EnemiesBar::setItems(vector<Entity*>* items)
{
	this->items = items;
	int count = 0;
	for (auto &item : *items)
	{
		if (!item->isAlive())
			count++;
	}

	stringstream ss;
	ss << count << "/" << items->size();
	counter.setString(ss.str());
}

TimeBar::TimeBar() : HUDBar()
{
	delete items;
	iconTexture.loadFromFile("resources/textures/hud/clock.png");
	icon.setTexture(iconTexture);
}

void TimeBar::setTimeLeft(int timeLeft)
{
	this->timeLeft = timeLeft;
	
	int s, m, h;

	s = timeLeft % 60;
	timeLeft /= 60;
	m = timeLeft % 60;
	timeLeft /= 60;
	h = timeLeft;

	stringstream ss;
	
	if (h > 0)
		ss << ((h < 10) ? "0" : "") << h << ":";
	ss << ((m < 10) ? "0" : "") << m << ":";
	ss << ((s < 10) ? "0" : "") << s;

	counter.setString(ss.str());
}

void Player::handleMovement(BlocksVector &solidBlocks, View &view, Sprite &background)
{
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

	//cout << (int) (getPosition().x / WIDTH) << ";" << (int) (getPosition().y / WIDTH) << endl; //Debug: player position
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
}

int Player::getHealth()
{
	return health;
}

void Player::reset()
{
	Entity::reset();
	hud.setPosition(Vector2f(50, 20));

	setHealth(3);
	hud.getHealthBar()->setMaxHealth(3);
}

void Player::immunity()
{
	if(immunityTimer > 0)
		immunityTimer--;
	
	if(immunityTimer <= 0)
		setColor(Color::White);
}

void Player::animate()
{
	if (immunityTimer > 0)
	{
		if (animateClock.getElapsedTime().asMilliseconds() % 100 > 0)
			setColor(Color::Transparent);
		if(animateClock.getElapsedTime().asMilliseconds() % 100 > 50)
			setColor(Color::White);
	}
	Entity::animate();
}

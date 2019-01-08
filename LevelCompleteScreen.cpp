#include "LevelCompleteScreen.h"
#include "Game.h"
#include "utils.h"
#include <iostream>

using namespace std;

void LevelCompleteScreen::showUpHealtBar()
{
	if (!frame.isShownUp())
		return;

	bool fadedIn = false;

	fadedIn = healthBar.fadeIn(ANIMATION_TIME_CONSTANT);
	fadedIn = Utils::fadeIn(counters[0], ANIMATION_TIME_CONSTANT);

	if(!fadedIn)
		return;

	int elapsedTime = animationClock->getElapsedTime().asMilliseconds();
	int health = hud->getHealthBar()->getHealth();
	int difficultyMultiplier = Game::getInstance().getDifficultyMultiplier();

	for (int i = 1; i <= health; i++)
		if (elapsedTime >= ANIMATION_TIME_CONSTANT + i * ANIMATION_TIME_CONSTANT && elapsedTime < ANIMATION_TIME_CONSTANT + i * ANIMATION_TIME_CONSTANT * 2)
				healthBar.setHealth(i);

	if (elapsedTime >= ANIMATION_TIME_CONSTANT * 2 && elapsedTime < ANIMATION_TIME_CONSTANT * (health + 3))
	{
		counters[0].set(health * Game::HEALTH_SCORE * difficultyMultiplier);
		counters[0].count(ANIMATION_TIME_CONSTANT * health);
	}
	else if (elapsedTime >= ANIMATION_TIME_CONSTANT * (health + 3))
	{
		if (health == healthBar.getMaxHealth())
			counters[0].set((health * Game::HEALTH_SCORE + Game::HEALTH_SCORE_BONUS) * difficultyMultiplier, health * Game::HEALTH_SCORE * difficultyMultiplier);
		counters[0].count(ANIMATION_TIME_CONSTANT);
	}
}

void LevelCompleteScreen::showUpItemsBar()
{
	if (!frame.isShownUp())
		return;

	int elapsedTime = animationClock->getElapsedTime().asMilliseconds();
	int health = hud->getHealthBar()->getHealth();
	int difficultyMultiplier = Game::getInstance().getDifficultyMultiplier();

	if (elapsedTime < ANIMATION_TIME_CONSTANT * (health + 3))
		return;

	bool fadedIn = false;

	fadedIn = itemsBar.fadeIn(ANIMATION_TIME_CONSTANT);
	fadedIn = Utils::fadeIn(counters[1], ANIMATION_TIME_CONSTANT);

	if (!fadedIn)
		return;

	elapsedTime -= ANIMATION_TIME_CONSTANT * (health + 3);

	hudBarCounting(*hud->getItemsBar(), itemsBar, elapsedTime, 1, Game::ITEMS_SCORE * difficultyMultiplier, Game::ITEMS_SCORE_BONUS * difficultyMultiplier);
}

void LevelCompleteScreen::showUpEnemiesBar()
{
	if (!frame.isShownUp())
		return;

	int elapsedTime = animationClock->getElapsedTime().asMilliseconds();
	int health = hud->getHealthBar()->getHealth();
	int difficultyMultiplier = Game::getInstance().getDifficultyMultiplier();

	if (elapsedTime < ANIMATION_TIME_CONSTANT * (health + 3 + 3))
		return;

	bool fadedIn = false;

	fadedIn = enemiesBar.fadeIn(ANIMATION_TIME_CONSTANT);
	fadedIn = Utils::fadeIn(counters[2], ANIMATION_TIME_CONSTANT);

	if (!fadedIn)
		return;

	elapsedTime -= ANIMATION_TIME_CONSTANT * (health + 3 + 3);

	hudBarCounting(*hud->getEnemiesBar(), enemiesBar, elapsedTime, 2, Game::ENEMIES_SCORE * difficultyMultiplier, Game::ENEMIES_SCORE_BONUS * difficultyMultiplier);
}

void LevelCompleteScreen::hudBarCounting(HUDBar &sourceHUDBar, HUDBar &targetHUDBar, int elapsedTime, int counterIndex, int score, int bonusScore)
{
	int items = sourceHUDBar.getCurrentItems();
	int maxItems = sourceHUDBar.getMaxItems();

	if (elapsedTime >= ANIMATION_TIME_CONSTANT && elapsedTime < ANIMATION_TIME_CONSTANT * 2)
		targetHUDBar.HUDBar::setItems((double)items / (ANIMATION_TIME_CONSTANT) * (elapsedTime - ANIMATION_TIME_CONSTANT), maxItems);
	else
		targetHUDBar.HUDBar::setItems(items, maxItems);

	if (elapsedTime >= ANIMATION_TIME_CONSTANT && elapsedTime < ANIMATION_TIME_CONSTANT * 3)
	{
		counters[counterIndex].set(items * score);
		counters[counterIndex].count(ANIMATION_TIME_CONSTANT);
	}
	else if (elapsedTime >= ANIMATION_TIME_CONSTANT * 3)
	{
		if (items == maxItems)
			counters[counterIndex].set(items * score + bonusScore, items * score);
		counters[counterIndex].count(ANIMATION_TIME_CONSTANT);
	}
}

void LevelCompleteScreen::showUpTimeBar()
{
	if (!frame.isShownUp())
		return;

	int elapsedTime = animationClock->getElapsedTime().asMilliseconds();
	int health = hud->getHealthBar()->getHealth();
	int difficultyMultiplier = Game::getInstance().getDifficultyMultiplier();

	if (elapsedTime < ANIMATION_TIME_CONSTANT * (health + 3 + 3 + 3))
		return;

	bool fadedIn = false;

	fadedIn = timeBar.fadeIn(ANIMATION_TIME_CONSTANT);
	fadedIn = Utils::fadeIn(counters[3], ANIMATION_TIME_CONSTANT);

	if (!fadedIn)
		return;

	elapsedTime -= ANIMATION_TIME_CONSTANT * (health + 3 + 3 + 3);

	int timeLeft = hud->getTimeBar()->getTimeLeft();

	if (elapsedTime >= ANIMATION_TIME_CONSTANT && elapsedTime < ANIMATION_TIME_CONSTANT * 2)
		timeBar.setTimeLeft((double)-timeLeft / ANIMATION_TIME_CONSTANT * (elapsedTime - ANIMATION_TIME_CONSTANT) + timeLeft);
	else
		timeBar.setTimeLeft(0);

	if (elapsedTime >= ANIMATION_TIME_CONSTANT && elapsedTime < ANIMATION_TIME_CONSTANT * 3)
	{
		counters[3].set(timeLeft * Game::TIME_SCORE * difficultyMultiplier);
		counters[3].count(ANIMATION_TIME_CONSTANT);
	}
}

void LevelCompleteScreen::showUpScore()
{
	if (!frame.isShownUp())
		return;

	int elapsedTime = animationClock->getElapsedTime().asMilliseconds();
	int health = hud->getHealthBar()->getHealth();

	if (elapsedTime < ANIMATION_TIME_CONSTANT * (health + 3 + 3 + 3 + 3))
		return;

	bool fadedIn = false;

	fadedIn = Utils::fadeIn(scoreText, ANIMATION_TIME_CONSTANT);
	fadedIn = Utils::fadeIn(counters[4], ANIMATION_TIME_CONSTANT);

	if (!fadedIn)
		return;

	elapsedTime -= ANIMATION_TIME_CONSTANT * (health + 3 + 3 + 3 + 3);
	
	int score = 0;
	
	for (int i = 0; i < 4; i++)
		score += counters[i].getEnd();

	if (elapsedTime >= ANIMATION_TIME_CONSTANT && elapsedTime < ANIMATION_TIME_CONSTANT * 3)
	{
		counters[4].set(score);
		counters[4].count(ANIMATION_TIME_CONSTANT);
	}
}

LevelCompleteScreen::LevelCompleteScreen(HUD * hud, Vector2f position)
{
	setSize(Vector2f(Game::WIDTH * 0.8, Game::HEIGHT * 0.7));
	setPosition(position);
	setHeader("Poziom ukonczony");
	this->hud = hud;
	
	healthBar.setMaxHealth(hud->getHealthBar()->getMaxHealth());
	healthBar.setHealth(0);
	healthBar.setPosition(Vector2f(50, 60));
	healthBar.hide();

	itemsBar.HUDBar::setItems(0, hud->getItemsBar()->getMaxItems());
	itemsBar.setPosition(Vector2f(50, 120));
	itemsBar.hide();

	enemiesBar.HUDBar::setItems(0, hud->getEnemiesBar()->getMaxItems());
	enemiesBar.setPosition(Vector2f(50, 180));
	enemiesBar.hide();
	
	timeBar.setTimeLeft(hud->getTimeBar()->getTimeLeft());
	timeBar.setPosition(Vector2f(50, 240));
	timeBar.hide();

	font.loadFromFile("resources/fonts/verdana.ttf");
	scoreText.setFont(font);
	scoreText.setString("Wynik:");
	scoreText.setPosition(Vector2f(50, 300));
	scoreText.setFillColor(Color(255, 255, 255, 0));
	scoreText.setOutlineColor(Color(0, 0, 0, 0));
	scoreText.setOutlineThickness(1);
	scoreText.setStyle(Text::Bold);

	Button mainMenuButton(Vector2f(100, 50), "Menu");
	Button restartButton(Vector2f(100, 50), "Restart");
	Button nextLevelButton(Vector2f(200, 50), "Nastepny poziom");

	menu.add(mainMenuButton);
	menu.add(restartButton);

	if(Utils::fexists(Level::LEVEL_PATH + Game::getInstance().getNextLevelFilename()))
		menu.add(nextLevelButton);

	Vector2f mp = menu.getSize();
	menu.setOrigin(Vector2f(mp.x / 2, mp.y / 2));

	menu.setOnClickListener(onClickListener);

	container.append(healthBar);
	container.append(itemsBar);
	container.append(enemiesBar);
	container.append(timeBar);
	container.append(scoreText);

	for (int i = 0; i < 5; i++)
	{
		counters[i].setPosition(Vector2f(400, 60 + i * 60));
		Color color = counters[i].getFillColor();
		Color outlineColor = counters[i].getOutlineColor();

		color.a = 0;
		outlineColor.a = 0;

		counters[i].setFillColor(color);
		counters[i].setOutlineColor(outlineColor);

		container.append(counters[i]);
	}

	counters[4].setStyle(Text::Bold);
}

void LevelCompleteScreen::draw(RenderWindow & window)
{
	if (frame.isShownUp())
		if (animationClock == NULL)
			animationClock = new Clock();

	showUpHealtBar();
	showUpItemsBar();
	showUpEnemiesBar();
	showUpTimeBar();
	showUpScore();

	LevelEndScreen::draw(window);
}

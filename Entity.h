#pragma once

#include <SFML/Graphics.hpp>
#include "BlocksVector.h"

using namespace std;
using namespace sf;

class Entity : public Sprite
{
protected:
	const string RES_DIR = "resources/textures/entities/";
	Texture *texture;
	static map<string, Texture*> textures;
	void loadTexture(string texture);
	double yVelocityDown;
	double yVelocityUp;
	bool jumping;
	int isMovingX;	//-1 w lewo, 0 false, 1 w prawo
	int isMovingY;	//-1 w górê, 0 false, 1 w dó³
	Clock animateClock;
	bool flags[1] = { 0 };
	bool active;
	bool alive;
	bool immortal;
	int animationStep;
	float WIDTH;

public:
	enum Flags {
		SMART
	};
	Entity();
	void setTexture(string texture);
	void reset();
	void setPosition(int x, int y);
	void handleGravity(BlocksVector &blocks, float gravity = 10);
	bool canGoRight(BlocksVector &blocks);
	bool canGoLeft(BlocksVector &blocks);
	bool canGoUp(BlocksVector & blocks);
	bool canGoDown(BlocksVector & blocks);
	virtual void handleMovement(BlocksVector &solidBlocks);
	void jump(double offset = 0);
	void setJumping(bool jumping);
	bool isJumping();
	void animate();
	void setMovingDirectionX(int x);
	void setMovingDirectionY(int y);
	int getMovingDirectionX();
	int getMovingDirectionY();
	bool getFlag(Flags flag);
	bool getFlag(string flag);
	void setFlag(Flags flag, bool value);
	void setFlag(string flag, bool value);
	Flags getFlagByName(string name);
	bool isActive();
	void activate();
	void deactivate();
	bool isAlive();
	void die();
	bool isImmortal();
	const float getWidth() const;
	static void flushTextures();
};
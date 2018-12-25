#include "Save.h"

Save::Save()
{
	slot = 1;
	level = 1;
	difficulty = 0;
}

void Save::setSlot(int slot)
{
	this->slot = slot;
}

void Save::setLevel(int level)
{
	this->level = level;
}

void Save::setDifficulty(int difficulty)
{
	this->difficulty = difficulty;
}

int Save::getSlot()
{
	return slot;
}

int Save::getLevel()
{
	return level;
}

int Save::getDifficulty()
{
	return difficulty;
}

void Save::write()
{
	//save file
}

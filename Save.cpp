#include "Save.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "utils.h"

using namespace std;

Save::Save()
{
	slot = 1;
	level = 1;
	difficulty = 0;
	
	for (int i = 0; i < 5; i++)
		highScores[i] = 0;
}

void Save::setSlot(int slot)
{
	this->slot = slot;
}

void Save::setLevel(int level)
{
	stringstream levelPath;
	levelPath << "resources/levels/level" << level << ".lvl";
	if (!Utils::fexists(levelPath.str()))
		level--;
	this->level = level;
}

void Save::setDifficulty(int difficulty)
{
	this->difficulty = difficulty;
}

void Save::setHighScore(int level, int highScore)
{
	highScores[level] = highScore;
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

int Save::getHighScore(int level)
{
	return highScores[level];
}

void Save::write()
{
	stringstream saveFilePath;
	saveFilePath << "saves/save" << slot << ".dat";
	ofstream ofs(saveFilePath.str(), fstream::binary);

	if (!ofs.is_open())
		return;

	ofs.write((char *) this, sizeof(*this));

	ofs.close();
}

void Save::read()
{
	stringstream saveFilePath;
	saveFilePath << "saves/save" << slot << ".dat";
	ifstream ifs(saveFilePath.str(), fstream::binary);

	if (!ifs.is_open())
		return;

	ifs.read((char *) this, sizeof(*this));

	ifs.close();
}

bool Save::exists()
{
	stringstream saveFilePath;
	saveFilePath << "saves/save" << slot << ".dat";
	return Utils::fexists(saveFilePath.str());
}
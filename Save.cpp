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
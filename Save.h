#pragma once
#include <map>
#include <string>

using namespace std;

class Save
{
private:
	int slot;
	int level;
	int difficulty;
	int highScores[5];
public:
	Save();
	void setSlot(int slot);
	void setLevel(int level);
	void setDifficulty(int difficulty);
	void setHighScore(int level, int highScore);
	int getSlot();
	int getLevel();
	int getDifficulty();
	int getHighScore(int level);
	void write();
	void read();
	bool exists();
};


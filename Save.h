#pragma once
class Save
{
private:
	int slot;
	int level;
	int difficulty;
public:
	Save();
	void setSlot(int slot);
	void setLevel(int level);
	void setDifficulty(int difficulty);
	int getSlot();
	int getLevel();
	int getDifficulty();
	void write();
};


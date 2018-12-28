#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Counter : public Text
{
private:
	Font font;
	int start;
	int current;
	int end;
	//Clock animationClock;
	Clock *animationClock;
	void update();
public:
	Counter();
	Counter(int end, int start = 0);
	void set(int end);
	void set(int end, int start);
	void reset();
	void count(int duration);
	int getStart();
	//int getCurrent();
	int getEnd();
};


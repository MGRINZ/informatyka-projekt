#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Counter : public Text
{
private:
	Font font;
	int current;
	int max;
	Clock *animationClock;
	void update();
public:
	Counter();
	Counter(int max, int current = 0);
	void set(int max);
	void set(int max, int current);
	void reset();
	void count(int duration);
	int getCurrent();
	int getMax();
};


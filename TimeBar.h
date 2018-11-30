#pragma once

#include "HUDBar.h"

class TimeBar : public HUDBar
{
private:
	int timeLeft = 0;
public:
	TimeBar();
	void setTimeLeft(int timeLeft);
	int getTimeLeft();
};
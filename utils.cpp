#define _CRT_SECURE_NO_DEPRECATE
#include "utils.h"

using namespace std;

int Utils::fadeIn(Sprite &object, int duration, int maxTransparency)
{
	Color color = object.getColor();

	int status = fadeIn1<Sprite>(object, duration, color, maxTransparency);
	
	object.setColor(color);

	return status;
}

bool Utils::fexists(string filename)
{
	FILE * fp = fopen(filename.c_str(), "r");
	if (fp)
	{
		fclose(fp);
		return true;
	}
	return false;
}

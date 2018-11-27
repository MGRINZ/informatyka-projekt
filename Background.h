#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Background : public Sprite
{
private:
	Texture texture;
	string name;
public:
	Background() {};
	void setTexture(string texture);
};

#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Block : public RectangleShape
{
private:
	const string RES_DIR = "resources/textures/blocks/";
protected:
	Texture* texture = new Texture;
public:
	static const float WIDTH;
	Block(int x, int y);
	Block(int x, int y, string texture);
	void setPosition(int x, int y);
};

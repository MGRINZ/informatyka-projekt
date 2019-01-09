#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Block : public RectangleShape
{
private:
	const string RES_DIR = "resources/textures/blocks/";
protected:
	static map<string, Texture*> textures;
	void loadTexture(string texture);
	Texture* texture;
public:
	static const float WIDTH;
	Block(int x, int y);
	Block(int x, int y, string texture);
	void setPosition(int x, int y);
};

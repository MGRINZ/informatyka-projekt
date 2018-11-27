#include "Background.h"

void Background::setTexture(string texture)
{
	name = texture;
	if (!texture.empty())
	{
		this->texture.loadFromFile("resources/backgrounds/" + texture);
		Sprite::setTexture(this->texture);
	}
}

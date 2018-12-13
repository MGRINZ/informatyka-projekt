#include "Button.h"

Button::Button(Vector2f size)
{
	normalTexture.loadFromFile("resources/textures/gui/button.png");
	pushedTexture.loadFromFile("resources/textures/gui/button-d.png");

	corners[0].setOrigin(Vector2f(15, 15));
	corners[1].setOrigin(Vector2f(0, 15));
	corners[2].setOrigin(Vector2f(0, 0));
	corners[3].setOrigin(Vector2f(15, 0));

	edges[0].setOrigin(Vector2f(0, 15));
	edges[1].setOrigin(Vector2f(0, 0));
	edges[2].setOrigin(Vector2f(0, 0));
	edges[3].setOrigin(Vector2f(15, 0));

	for (int i = 0; i < 4; i++)
	{
		corners[i].setTexture(normalTexture);
		edges[i].setTexture(normalTexture);
	}

	filling.setTexture(normalTexture);

	corners[0].setTextureRect(IntRect(0, 0, 15, 15));
	corners[1].setTextureRect(IntRect(85, 0, 15, 15));
	corners[2].setTextureRect(IntRect(85, 35, 15, 15));
	corners[3].setTextureRect(IntRect(0, 35, 15, 15));

	edgesTextureRects[0] = IntRect(15, 0, 70, 15);
	edgesTextureRects[1] = IntRect(85, 15, 15, 20);
	edgesTextureRects[2] = IntRect(15, 35, 70, 15);
	edgesTextureRects[3] = IntRect(0, 15, 15, 20);

	fillingTextureRect = IntRect(15, 15, 70, 20);

	setSize(size);
}

void Button::draw(RenderTarget & target, RenderStates states) const
{
	for (int i = 0; i < 4; i++)
	{
		target.draw(corners[i]);
		//target.draw(edges[i]);	//!!!!!!!!!!!!!!!!!!!!!!
		for(auto &edge : edgesGroups[i])
			target.draw(edge);
		for(auto &part : fillingGroup)
			target.draw(part);
	}
	//target.draw(filling);
}

void Button::setSize(Vector2f size)
{
	if (size.x < 30)
		size.x = 30;
	if (size.y < 30)
		size.y = 30;

	this->size = size;
	setPositiion(position);
}

void Button::setPositiion(Vector2f position)
{
	corners[0].setPosition(Vector2f(position.x, position.y));
	corners[1].setPosition(Vector2f(position.x + (size.x - 30), position.y));
	corners[2].setPosition(Vector2f(position.x + (size.x - 30), position.y + (size.y - 30)));
	corners[3].setPosition(Vector2f(position.x, position.y + (size.y - 30)));

	int horizontalEdges = (size.x - 30) / 70;
	int verticalEdges = (size.y - 30) / 20;

	IntRect etr;

	fillingGroup.resize((horizontalEdges + 1) * (verticalEdges + 1));

	for (int i = 0; i < horizontalEdges + 1; i++)
	{	
		if (i >= edgesGroups[0].size())
			edgesGroups[0].push_back(edges[0]);
		edgesGroups[0][i].setPosition(Vector2f(position.x + i * 70, position.y));
		etr = edgesTextureRects[0];
		if (i == horizontalEdges)
			etr.width = ((int) size.x - 30) % 70;
		edgesGroups[0][i].setTextureRect(etr);
		

		if (i >= edgesGroups[2].size())
			edgesGroups[2].push_back(edges[2]);
		edgesGroups[2][i].setPosition(Vector2f(position.x + i * 70, position.y + (size.y - 30)));
		etr = edgesTextureRects[2];
		if (i == horizontalEdges)
			etr.width = ((int) size.x - 30) % 70;
		edgesGroups[2][i].setTextureRect(etr);

		fillingGroup[i] = filling;
		fillingGroup[i].setPosition(position.x + i * 70, position.y);
		etr = fillingTextureRect;
		if (i == horizontalEdges)
			etr.width = ((int)size.x - 30) % 70;
		fillingGroup[i].setTextureRect(etr);
	}

	for (int i = 0; i < verticalEdges + 1; i++)
	{
		if (i >= edgesGroups[1].size())
			edgesGroups[1].push_back(edges[1]);
		edgesGroups[1][i].setPosition(Vector2f(position.x + (size.x - 30), position.y + i * 20));
		etr = edgesTextureRects[1];
		if (i == verticalEdges)
			etr.height = ((int)size.y - 30) % 20;
		edgesGroups[1][i].setTextureRect(etr);


		if (i >= edgesGroups[3].size())
			edgesGroups[3].push_back(edges[3]);
		edgesGroups[3][i].setPosition(Vector2f(position.x, position.y + i * 20));
		etr = edgesTextureRects[3];
		if (i == verticalEdges)
			etr.height = ((int)size.y - 30) % 20;
		edgesGroups[3][i].setTextureRect(etr);

		if (i >= 1)
		{
			for (int j = 0; j < horizontalEdges + 1; j++)
			{
				fillingGroup[i * (horizontalEdges + 1) + j] = fillingGroup[(i - 1) * (horizontalEdges + 1) + j];
				fillingGroup[i * (horizontalEdges + 1) + j].move(Vector2f(0, 20));
				etr = fillingGroup[i * (horizontalEdges + 1) + j].getTextureRect();
				if (i == verticalEdges)
					etr.height = ((int)size.y - 30) % 20;
				fillingGroup[i * (horizontalEdges + 1) + j].setTextureRect(etr);
			}
		}
	}

	edgesGroups[0].resize(horizontalEdges + 1);
	edgesGroups[1].resize(verticalEdges + 1);
	edgesGroups[2].resize(horizontalEdges + 1);
	edgesGroups[3].resize(verticalEdges + 1);

	this->position = position;
}

void Button::setOrigin(Vector2f origin)
{
	this->origin = origin;
	setPositiion(position);
}

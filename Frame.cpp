#include "Frame.h"
#include "utils.h"
#include "Game.h"

Frame::Frame()
{
	cornersTextures[0].loadFromFile("resources/textures/gui/frame/frame_01.png");
	cornersTextures[1].loadFromFile("resources/textures/gui/frame/frame_03.png");
	cornersTextures[2].loadFromFile("resources/textures/gui/frame/frame_09.png");
	cornersTextures[3].loadFromFile("resources/textures/gui/frame/frame_07.png");
	edgesTextures[0].loadFromFile("resources/textures/gui/frame/frame_02.png");
	edgesTextures[1].loadFromFile("resources/textures/gui/frame/frame_06.png");
	edgesTextures[2].loadFromFile("resources/textures/gui/frame/frame_08.png");
	edgesTextures[3].loadFromFile("resources/textures/gui/frame/frame_04.png");

	//Ustawienie punktów odniesienia w œrodku tekstury
	corners[0].setOrigin(Vector2f(20, 20));
	corners[1].setOrigin(Vector2f(0, 20));
	corners[2].setOrigin(Vector2f(0, 0));
	corners[3].setOrigin(Vector2f(20, 0));

	//Wybranie z tekstury tylko æwiartki zawieraj¹cych naro¿nik
	corners[0].setTextureRect(IntRect(0, 0, 20, 20));
	corners[1].setTextureRect(IntRect(20, 0, 20, 20));
	corners[2].setTextureRect(IntRect(20, 20, 20, 20));
	corners[3].setTextureRect(IntRect(0, 20, 20, 20));

	//Ustawienie punktów odniesienia wzglêdem naro¿ników
	edges[0].setOrigin(Vector2f(0, 20));
	edges[1].setOrigin(Vector2f(0, 0));
	edges[2].setOrigin(Vector2f(0, 0));
	edges[3].setOrigin(Vector2f(20, 0));

	//Ukrycie nadmiaru tekstury
	edges[0].setTextureRect(IntRect(0, 0, 0, 40));
	edges[1].setTextureRect(IntRect(0, 0, 40, 0));
	edges[2].setTextureRect(IntRect(0, 20, 0, 20));
	edges[3].setTextureRect(IntRect(0, 0, 40, 0));

	//Ustawienie domyœlnego rozwiniêcia zawartoœci
	container.setTexture(Texture());	//setTextureRect nie zadzia³a dopóki nie bêdzie ¿adnej tekstury
	container.setTextureRect(IntRect(0, 0, 0, 0));

	for (int i = 0; i < 4; i++)
	{
		corners[i].setTexture(cornersTextures[i]);
		corners[i].setColor(Color(255, 255, 255, 0));
		edges[i].setTexture(edgesTextures[i]);
		edgesTextures[i].setRepeated(true);
	}
}

Frame::~Frame()
{
	if (animationClock != NULL)
		delete animationClock;
}

void Frame::showUp(int duration) //duration – czas trwania animacji rozszerzania szerokoœci lub wysokoœci ramki ramki w ms; 2 * duration - czas animacji
{
	if (shownUp)
		return;

	int fadedIn = 0;
	for (int i = 0; i < 4; i++)
		fadedIn = Utils::fadeIn(corners[i], 100);	//fadeIn zwraca 1 jeœli obiekt jest ju¿ widoczny

	//Dopóki obiekt nie jest widoczny nic nie rób
	if (!fadedIn)
		return;

	if (animationClock == NULL)
		animationClock = new Clock();
	int elapsedTime = animationClock->getElapsedTime().asMilliseconds();

	//Rozszerzanie szerokoœci
	if (elapsedTime <= duration)
	{
		//Rozszerzanie rogów
		for (int i = 0; i < 4; i++)
		{
			Vector2f cp = corners[i].getPosition();
			IntRect ctr = corners[i].getTextureRect();

			//Przesuwanie rogów po lewej
			if (i == 0 || i == 3)
				cp.x = position.x -(size.x / 2) / duration * elapsedTime;
			//Przesuwanie rogów po prawej
			else
			{
				cp.x = (position.x + (size.x / 2) / duration * elapsedTime);
				ctr.left = 20 - ceil(20.0 / duration * elapsedTime);	//Rozszerzanie obszaru tekstury w poziomie (na potrzebê poprawnie wyœwietlanych naro¿ników)
			}
			ctr.width = 20 + ceil(20.0 / duration * elapsedTime);	//Rozszerzanie obszaru tekstury (na potrzebê poprawnie wyœwietlanych naro¿ników)
			corners[i].setPosition(cp);
			corners[i].setTextureRect(ctr);
		}

		//Rozszerzanie poziomych krawêdzi
		Vector2f cp;
		IntRect etr;

		cp = corners[0].getPosition();
		etr = edges[0].getTextureRect();
		etr.width = corners[1].getPosition().x - cp.x;
		edges[0].setPosition(cp);
		edges[0].setTextureRect(etr);

		cp = corners[3].getPosition();
		etr = edges[2].getTextureRect();
		etr.width = corners[2].getPosition().x - cp.x;
		edges[2].setPosition(cp);
		edges[2].setTextureRect(etr);

		//Rozszerzanie zawartoœci
		IntRect ctr = container.getTextureRect();
		etr = edges[0].getTextureRect();
		ctr.width = etr.width;
		container.setTextureRect(ctr);
	}
	//Rozszerzanie wysokoœci
	else if (elapsedTime > duration && elapsedTime <= duration * 2)
	{
		//Rozszerzanie rogów
		for (int i = 0; i < 4; i++)
		{
			Vector2f cp = corners[i].getPosition();
			IntRect ctr = corners[i].getTextureRect();

			//Rozszerzanie rogów u góry
			if (i == 0 || i == 1)
				cp.y = position.y -(size.y / 2) / duration * (elapsedTime - duration); //(size.x / 2) / duration * (elapsedTime - prevDuration)
			//Rozszerzanie rogów na dole
			else
			{
				cp.y = position.y + (size.y / 2 - 20) / duration * (elapsedTime - duration); //(size.x / 2) / duration * (elapsedTime - prevDuration)
				ctr.top = 20 - ceil(20.0 / duration * (elapsedTime - duration));	//Rozszerzanie obszaru tekstury w poziomie (na potrzebê poprawnie wyœwietlanych naro¿ników)
			}
			ctr.height = 20 + ceil(20.0 / duration * (elapsedTime - duration));	//Rozszerzanie obszaru tekstury w poziomie (na potrzebê poprawnie wyœwietlanych naro¿ników)
			corners[i].setPosition(Vector2f(cp.x, cp.y));
			corners[i].setTextureRect(ctr);
		}

		//Wyrównanie rogów w poziomie
		Vector2f cp;

		cp = corners[0].getPosition();
		cp.x = position.x - (size.x / 2);
		corners[0].setPosition(cp);

		cp = corners[3].getPosition();
		cp.x = position.x - (size.x / 2);
		corners[3].setPosition(cp);

		cp = corners[1].getPosition();
		cp.x = position.x + (size.x / 2) - 20;
		corners[1].setPosition(cp);

		cp = corners[2].getPosition();
		cp.x = position.x + (size.x / 2) - 20;
		corners[2].setPosition(cp);

		//Rozszerzenie obszaru tekstury rogów w poziomie
		IntRect ctr;
		for (int i = 0; i < 4; i++)
		{
			ctr = corners[i].getTextureRect();
			ctr.left = 0;
			ctr.width = 40;
			corners[i].setTextureRect(ctr);
		}

		//Wyrównianie poziomych krawêdzi
		IntRect etr;

		etr = edges[0].getTextureRect();
		etr.width = corners[1].getPosition().x - corners[0].getPosition().x;
		edges[0].setTextureRect(etr);

		etr = edges[2].getTextureRect();
		etr.width = corners[2].getPosition().x - corners[3].getPosition().x;
		edges[2].setTextureRect(etr);

		//Przesuniêcie poziomych krawêdzi
		cp = corners[0].getPosition();
		edges[0].setPosition(cp);

		cp = corners[3].getPosition();
		cp.y += corners[3].getTextureRect().height - 20;	//Przesuniêcie obiektu ze wzglêdu na zmianê rozmiaru naro¿nika
		edges[2].setPosition(cp);
		
		//Wyrównanie szerokoœci zawartoœci
		ctr = container.getTextureRect();
		etr = edges[0].getTextureRect();
		ctr.width = etr.width + 20;
		container.setTextureRect(ctr);

		//Rozszerzanie pionowych krawêdzi

		cp = corners[1].getPosition();
		etr = edges[1].getTextureRect();
		etr.height = corners[2].getPosition().y - cp.y + 20;
		edges[1].setPosition(cp);
		edges[1].setTextureRect(etr);

		cp = corners[0].getPosition();
		etr = edges[3].getTextureRect();
		etr.height = corners[3].getPosition().y - cp.y + 20;
		edges[3].setPosition(cp);
		edges[3].setTextureRect(etr);

		//Rozszerzanie zawartoœci
		cp = corners[0].getPosition();
		ctr = container.getTextureRect();
		ctr.top = size.y / 2 - (position.y - cp.y);
		ctr.height = (position.y - cp.y) * 2;
		container.setTextureRect(ctr);
	}
	//Po zakoñczeniu animacji
	else
	{
		//Wyrównanie rogów w pionie
		Vector2f cp;

		cp = corners[0].getPosition();
		cp.y = position.y - (size.y / 2);
		corners[0].setPosition(cp);

		cp = corners[3].getPosition();
		cp.y = position.y + (size.y / 2) - 20;
		corners[3].setPosition(cp);
		
		cp = corners[1].getPosition();
		cp.y = position.y - (size.y / 2);
		corners[1].setPosition(cp);

		cp = corners[2].getPosition();
		cp.y = position.y + (size.y / 2) - 20;
		corners[2].setPosition(cp);

		//Rozszerzenie obszaru tekstury rogów w pionie
		IntRect ctr;
		for (int i = 0; i < 4; i++)
		{
			ctr = corners[i].getTextureRect();
			ctr.top = 0;
			ctr.height = 40;
			corners[i].setTextureRect(ctr);
		}

		//Wyrównianie pionowych krawêdzi
		IntRect etr;

		etr = edges[1].getTextureRect();
		etr.height = corners[2].getPosition().y - corners[1].getPosition().y;
		edges[1].setTextureRect(etr);

		etr = edges[3].getTextureRect();
		etr.height = corners[3].getPosition().y - corners[0].getPosition().y;
		edges[3].setTextureRect(etr);

		//Przesuniêcie pionowych krawêdzi
		cp = corners[0].getPosition();
		edges[3].setPosition(cp);

		cp = corners[1].getPosition();
		edges[1].setPosition(cp);
		
		//Przesuniêcie poziomych krawêdzi
		cp = corners[0].getPosition();
		edges[0].setPosition(cp);

		cp = corners[3].getPosition();
		cp.y += corners[3].getTextureRect().height - 20;	//Przesuniêcie obiektu ze wzglêdu na zmianê rozmiaru naro¿nika
		edges[2].setPosition(cp);

		//Wyrównanie wysokoœci zawartoœci
		ctr = container.getTextureRect();
		etr = edges[3].getTextureRect();
		ctr.top = 0;
		ctr.height = etr.height + 20;
		container.setTextureRect(ctr);
		
		shownUp = true;
		delete animationClock;
		animationClock = NULL;
	}
}

void Frame::show()
{
	for (int i = 0; i < 4; i++)
		corners[i].setColor(Color(255, 255, 255, 255));

	corners[0].setPosition(Vector2f(position.x - (size.x / 2), position.y - (size.y / 2)));
	corners[1].setPosition(Vector2f(position.x + (size.x / 2) - 20, position.y - (size.y / 2)));
	corners[2].setPosition(Vector2f(position.x + (size.x / 2) - 20, position.y + (size.y / 2) - 20));
	corners[3].setPosition(Vector2f(position.x - (size.x / 2), position.y + (size.y / 2) - 20));

	for (int i = 0; i < 4; i++)
		corners[i].setTextureRect(IntRect(0, 0, 40, 40));

	Vector2f cp;
	IntRect etr;

	cp = corners[0].getPosition();
	etr = edges[0].getTextureRect();
	etr.width = corners[1].getPosition().x - cp.x;
	edges[0].setPosition(cp);
	edges[0].setTextureRect(etr);

	cp = corners[3].getPosition();
	cp.y += 20;
	etr = edges[2].getTextureRect();
	etr.width = corners[2].getPosition().x - cp.x;
	edges[2].setPosition(cp);
	edges[2].setTextureRect(etr);

	cp = corners[1].getPosition();
	etr = edges[1].getTextureRect();
	etr.height = corners[2].getPosition().y - cp.y + 20;
	edges[1].setPosition(cp);
	edges[1].setTextureRect(etr);

	cp = corners[0].getPosition();
	etr = edges[3].getTextureRect();
	etr.height = corners[3].getPosition().y - cp.y + 20;
	edges[3].setPosition(cp);
	edges[3].setTextureRect(etr);

	IntRect ctr = container.getTextureRect();
	etr = edges[0].getTextureRect();
	ctr.top = 0;
	ctr.width = etr.width + 20;
	etr = edges[3].getTextureRect();
	ctr.height = etr.height + 20;
	container.setTextureRect(ctr);

	setPosition(position);

	shownUp = true;

}

bool Frame::isShownUp()
{
	return shownUp;
}

void Frame::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(container);
	for(int i = 0; i < 4; i++)
	{
		target.draw(edges[i]);
		target.draw(corners[i]);
	}
	
}

void Frame::setPosition(Vector2f position)
{
	for (int i = 0; i < 4; i++)
	{
		Vector2f cp = corners[i].getPosition();
		cp.x = position.x + cp.x - this->position.x;
		cp.y = position.y + cp.y - this->position.y;
		corners[i].setPosition(cp);

		Vector2f ep = edges[i].getPosition();
		ep.x = position.x + ep.x - this->position.x;
		ep.y = position.y + ep.y - this->position.y;
		edges[i].setPosition(ep);
	}

	Vector2f cp = corners[0].getPosition();
	container.setPosition(cp);

	this->position = position;
}

Vector2f Frame::getPosition()
{
	return position;
}

void Frame::setSize(Vector2f size)
{
	this -> size = size;
}

Vector2f Frame::getSize()
{
	return size;
}

Sprite * Frame::getContainer()
{
	return &container;
}

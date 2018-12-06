#include "Frame.h"
#include "utils.h"
#include "Game.h"

Frame::Frame()
{
	cornersTextures[0].loadFromFile("resources/textures/frame/frame_01.png");
	cornersTextures[1].loadFromFile("resources/textures/frame/frame_03.png");
	cornersTextures[2].loadFromFile("resources/textures/frame/frame_09.png");
	cornersTextures[3].loadFromFile("resources/textures/frame/frame_07.png");
	edgesTextures[0].loadFromFile("resources/textures/frame/frame_02.png");
	edgesTextures[1].loadFromFile("resources/textures/frame/frame_06.png");
	edgesTextures[2].loadFromFile("resources/textures/frame/frame_08.png");
	edgesTextures[3].loadFromFile("resources/textures/frame/frame_04.png");

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

	for (int i = 0; i < 4; i++)
	{
		corners[i].setTexture(cornersTextures[i]);
		corners[i].setColor(Color(255, 255, 255, 0));
		edges[i].setTexture(edgesTextures[i]);
		edgesTextures[i].setRepeated(true);
	}

	size = Vector2f(Game::WIDTH * 0.8, Game::HEIGHT * 0.5); //??? Czy tak zostanie
}

void Frame::showUp()
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

	int duration = 250;	//Czas trwania animacji rozszerzania szerokoœci lub wysokoœci ramki ramki w ms; 2 * duration - czas animacji

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
				cp.x = position.x + (size.x / 2) / duration * elapsedTime;
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
		etr.width = (position.x - cp.x) * 2 + 2;	//+ 2 - uzupe³nienie brakuj¹cych pikseli przy rozszerzaniu
		edges[0].setPosition(cp);
		edges[0].setTextureRect(etr);

		cp = corners[3].getPosition();
		etr = edges[2].getTextureRect();
		etr.width = (position.x - cp.x) * 2 + 2;	//+ 2 - uzupe³nienie brakuj¹cych pikseli przy rozszerzaniu
		edges[2].setPosition(cp);
		edges[2].setTextureRect(etr);

		//Rozszerzanie zawartoœci

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
				cp.y = position.y -(size.y / 2) / duration * (elapsedTime - duration); //(size.x / 2) / (duration - prevDuration) * elapsedTime
			//Rozszerzanie rogów na dole
			else
			{
				cp.y = position.y + (size.y / 2) / duration * (elapsedTime - duration); //(size.x / 2) / (duration - prevDuration) * elapsedTime
				ctr.top = 20 - ceil(20.0 / duration * (elapsedTime - duration));	//Rozszerzanie obszaru tekstury w poziomie (na potrzebê poprawnie wyœwietlanych naro¿ników)
			}
			ctr.height = 20 + ceil(20.0 / duration * (elapsedTime - duration));	//Rozszerzanie obszaru tekstury w poziomie (na potrzebê poprawnie wyœwietlanych naro¿ników)
			corners[i].setPosition(Vector2f(cp.x, cp.y));
			corners[i].setTextureRect(ctr);
		}

		//Rozszerzanie pionowych krawêdzi
		Vector2f cp;
		IntRect etr;

		cp = corners[1].getPosition();
		etr = edges[1].getTextureRect();
		etr.height = (position.y - cp.y) * 2 + 2;	//+ 2 - uzupe³nienie brakuj¹cych pikseli przy rozszerzaniu
		edges[1].setPosition(cp);
		edges[1].setTextureRect(etr);

		cp = corners[0].getPosition();
		etr = edges[3].getTextureRect();
		etr.height = (position.y - cp.y) * 2 + 2;	//+ 2 - uzupe³nienie brakuj¹cych pikseli przy rozszerzaniu
		edges[3].setPosition(cp);
		edges[3].setTextureRect(etr);

		//Przesuniêcie poziomych krawêdzi
		cp = corners[0].getPosition();
		edges[0].setPosition(cp);

		cp = corners[3].getPosition();
		cp.y += corners[3].getTextureRect().height - 20;	//Przesuniêcie obiektu ze wzglêdu na zmianê rozmiaru naro¿nika
		edges[2].setPosition(cp);

		//Rozszerzanie zawartoœci

	}
	//Po zakoñczeniu animacji
	else
	{
		shownUp = true;
		delete animationClock;
	}
}

void Frame::draw(RenderWindow & window)
{
	showUp();
	for(int i = 0; i < 4; i++)
	{
		window.draw(edges[i]);
		window.draw(corners[i]);
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

	this->position = position;
}

Vector2f Frame::getPosition()
{
	return position;
}
#include "HelpMenu.h"
#include "HelpMenuOnClickListener.h"
#include "HelpMenuPausedOnClickListener.h"
#include "Game.h"

HelpMenu::HelpMenu()
{
	menuId = "HelpMenu";
	frame.setSize(Vector2f(Game::WIDTH - 140, Game::HEIGHT - 140));
	frame.setPosition(Vector2f(Game::WIDTH / 2, Game::HEIGHT / 2));
	frame.getContainer()->setTexture(*container.getTexture(), false);
	frame.show();

	container.setSize(Vector2f(Game::WIDTH - 140, Game::HEIGHT - 140));
	container.setBackground(Color(0, 0, 0, 96));

	headers[0].setPosition(Vector2f(10, 10));
	paragraphs[0].setPosition(Vector2f(10, 50));
	paragraphs[1].setPosition(Vector2f(10, 100));
	headers[1].setPosition(Vector2f(10, 200));
	paragraphs[2].setPosition(Vector2f(10, 240));

	string text;
	text = "Jak grac?";
	headers[0].setString(text);
	text = "Twoim zadaniem jest przedostanie sie z jednego konca poziomu do drugiego,\nzbierajac przedmioty i unikajac zagrozenia.";
	paragraphs[0].setString(text);
	text = "Za kazdy zdobyty przedmiot, kazdego pokonanego przeciwnika, kazde\nzachowane zycie i za nadmiar czasu otrzymujesz punkty. ";
	text += "Zbierz wszystkie\nprzedmioty, pokonaj wszystkich przeciwnikow i zachowaj wszystkie zycia, aby\notrzymac bonus. ";
	text += "Im wyzszy stopien trudnosci, tym wieksza ilosc punktow.";
	paragraphs[1].setString(text);
	text = "Sterowanie";
	headers[1].setString(text);
	text = "Strzalki w lewo/prawo - poruszanie sie\n";
	text += "Strzalka w gore - skok";
	paragraphs[2].setString(text);

	for (int i = 0; i < 2; i++)
	{
		headers[i].setFont(Game::getInstance().getMainFont());
		headers[i].setCharacterSize(30);
		container.append(headers[i]);
	}

	for (int i = 0; i < 3; i++)
	{
		paragraphs[i].setFont(Game::getInstance().getMainFont());
		paragraphs[i].setCharacterSize(15);
		container.append(paragraphs[i]);
	}

	container.draw();

	Button backButton(Vector2f(300, 50), "Powrot");
	menu.add(backButton);

	setPosition(Vector2f(Game::WIDTH / 2, Game::HEIGHT - 150));

	onClickListener = new HelpMenuPausedOnClickListener();

	menu.setOnClickListener(*onClickListener);
}

HelpMenu::HelpMenu(GameMenu &gameMenu) : HelpMenu()
{
	onClickListener = new HelpMenuOnClickListener(gameMenu);

	menu.setOnClickListener(*onClickListener);
}

void HelpMenu::draw(RenderTarget & target, RenderStates states) const
{
	target.draw(frame);
	Menu::draw(target, states);
}

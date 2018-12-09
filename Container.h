#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Container
{
private:
	vector<Drawable*> drawables;
	RenderTexture texture;
	Vector2f size;
	Color background;
public:
	Container();
	Container(Vector2f size);
	template <class T>
	void append(T &drawable);
	const Texture *getTexture();
	void setSize(Vector2f size);
	Vector2f getSize();
	void draw();
	void setBackground(Color background);
};

template<class T>
inline void Container::append(T &drawable)
{
	drawables.push_back(&drawable);
}

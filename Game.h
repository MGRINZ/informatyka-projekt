#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Game
{
public:
	static const int width = 800;
	static const int height = 600;
};

class Block: public sf::RectangleShape
{
public:
	const float width = Game::height / 18.75;
	Block(int x, int y);
};

class Entity
{

};

class Level
{
private:
	vector<Block> blocks;
	vector<Entity> enemies;
	Entity player;
public:
	Level();
	void addBlock(Block block);
	void draw(RenderWindow &window);
};


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
private:
	Texture* texture = new Texture;
public:
	const float width = Game::height / 18.75;
	Block(int x, int y);
	Block(int x, int y, string texture);
	void setPosition(int x, int y);
};

class Entity
{

};

class Background : public Sprite
{
private:
	Texture texture;
	string name;
public:
	Background();
	void setTexture(String texture);
};

class Level
{
private:
	vector<Block> solidBlocks;
	vector<Block> backgroundBlocks;
	vector<Block> foregroundBlocks;
	vector<Entity> enemies;
	Entity player;
	string name;
	Background background;
	string audio;
public:
	Level();
	void addSolidBlock(Block block);
	void addBackgroundBlock(Block block);
	void addForegroundBlock(Block block);
	void draw(RenderWindow &window);
	int load(string levelName);
	static const int LEVEL_LOAD_SUCCESS = 0;
	static const int LEVEL_LOAD_ERROR_OPEN_FILE = 1;
	static const string LEVEL_PROPERTY_SETTINGS;
	static const string LEVEL_PROPERTY_TERRAIN;
	static const string LEVEL_PROPERTY_BACKGROUND;
	static const string LEVEL_PROPERTY_FOREGROUND;
	static const string LEVEL_PROPERTY_ENTITIES;
};
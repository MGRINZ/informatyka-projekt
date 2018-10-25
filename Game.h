#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Game
{
public:
	static const int WIDTH = 800;
	static const int HEIGHT = 600;
};

class Block: public sf::RectangleShape
{
private:
	Texture* texture = new Texture;
public:
	static const float WIDTH;
	Block(int x, int y);
	Block(int x, int y, string texture);
	void setPosition(int x, int y);
};

class Entity : public Sprite
{
private:
	Texture texture;

public:
	static const float WIDTH;
	Entity();
	void setPosition(int x, int y);
	void handleGravity(vector<Block> &blocks, float gravity = Block::WIDTH / 4);
	bool canGoRight(vector<Block> &blocks);
	bool canGoLeft(vector<Block> &blocks);
	void jump(vector<Block> &blocks);
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
	static const int LEVEL_LOAD_SUCCESS = 0;
	static const int LEVEL_LOAD_ERROR_OPEN_FILE = 1;
	static const string LEVEL_PROPERTY_SETTINGS;
	static const string LEVEL_PROPERTY_TERRAIN;
	static const string LEVEL_PROPERTY_BACKGROUND;
	static const string LEVEL_PROPERTY_FOREGROUND;
	static const string LEVEL_PROPERTY_ENTITIES;
	Level();
	void addSolidBlock(Block block);
	void addBackgroundBlock(Block block);
	void addForegroundBlock(Block block);
	void draw(RenderWindow &window);
	int load(string levelName);
	void handleEntities();
};
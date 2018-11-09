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

class BlocksVector : public vector<Block>
{
public:
	Block* getSolidBlockAtPosition(int x, int y);
};

class Item : public Block
{
private:
	bool active = true;
public:
	Item(int x, int y);
	Item(int x, int y, string texture);
	bool isActive();
	void disable();
};

class Entity : public Sprite
{
private:
	Texture texture;
	double yVelocityDown;
	double yVelocityUp;
	bool jumping;
	int isMovingX;	//-1 w lewo, 0 false, 1 w prawo
	int isMovingY;	//-1 w górê, 0 false, 1 w dó³
	Clock animateClock;
public:
	static const float WIDTH;
	Entity();
	void setPosition(int x, int y);
	void handleGravity(BlocksVector &blocks, float gravity = 10);
	bool canGoRight(BlocksVector &blocks);
	bool canGoLeft(BlocksVector &blocks);
	void jump(BlocksVector &blocks);
	void setJumping(bool jumping);
	bool isJumping();
	void animate();
	void setMovingDirectionX(int x);
	void setMovingDirectionY(int y);
	int getMovingDirectionX();
	int getMovingDirectionY();
	void takingItem(vector<Item> &items);
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
	BlocksVector solidBlocks;
	vector<Block> backgroundBlocks;
	vector<Block> foregroundBlocks;
	vector<Entity> enemies;
	vector<Item> items;
	Entity player;
	string name;
	Background background;
	string audio;
	View view;
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
	View getView();
};
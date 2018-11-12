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

class Block : public sf::RectangleShape
{
private:
	const string RES_DIR = "resources/textures/blocks/";
protected:
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
	const string RES_DIR = "resources/textures/";
	bool active = true;
	Clock animateClock;
public:
	Item(int x, int y);
	Item(int x, int y, string texture);
	bool isActive();
	void disable();
	void animate();
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
	void reset();
	void setPosition(int x, int y);
	void handleGravity(BlocksVector &blocks, float gravity = 10);
	void handleMovement(BlocksVector &solidBlocks, View &view, Sprite &background);
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
	void takingItem(Item &item);
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

class LevelEndScreen
{
private:
	Vector2f position;
	RectangleShape overlay;
	RectangleShape container;
	Font headerFont;
	Text header;
public:
	LevelEndScreen();
	void draw(RenderWindow &window);
	void setPosition(Vector2f position);
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
	Vector2u endPosition[2];
	LevelEndScreen endScreen;
	int status;

public:
	static const int LEVEL_LOAD_SUCCESS = 0;
	static const int LEVEL_LOAD_ERROR_OPEN_FILE = 1;
	static const string LEVEL_PROPERTY_SETTINGS;
	static const string LEVEL_PROPERTY_TERRAIN;
	static const string LEVEL_PROPERTY_BACKGROUND;
	static const string LEVEL_PROPERTY_FOREGROUND;
	static const string LEVEL_PROPERTY_ITEMS;
	static const string LEVEL_PROPERTY_ENTITIES;
	static const int LEVEL_STATUS_LOADING = 0;
	static const int LEVEL_STATUS_IN_GAME = 1;
	static const int LEVEL_STATUS_PAUSED = 2;
	static const int LEVEL_STATUS_FINISHED = 3;
	Level();
	void addSolidBlock(Block block);
	void addBackgroundBlock(Block block);
	void addForegroundBlock(Block block);
	void addItem(Item item);
	void draw(RenderWindow &window);
	int load(string levelName);
	void handleEntities();
	void handleItems();
	void handleFinish();
	View getView();
	int getStatus();
	void setStatus(int status);
};
#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"

#include "Enemy.h"
#include "Projectile.h"
#include "Text.h"
#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String
#include <list>

#include "Audio.h"
#include "Tile.h"
#include "Space.h" 
class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;

	void keysToControls(SDL_Event event);
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	int mapWidth;

	void calculateScroll();
	float scrollX;

	list<Tile*> tiles;

	Space* space;

	int newEnemyTime = 0;

	Player* player;
	Background* background;
	list<Enemy*> enemies;
	list<Projectile*> projectiles;

	bool controlShoot = false;
	int controlMoveY = 0;
	int controlMoveX = 0;

	Actor* backgroundPoints;
	Text* textPoints;
	int points;

	Audio* audioBackground;



};


#pragma once

#include "Layer.h"
#include "Background.h"

#include "Enemy.h"
#include "RedEnemy.h"
#include "BlueEnemy.h"
#include "StandardEnemy.h"
#include "Projectile.h"
#include "EnemyProjectile.h"
#include "Text.h"
#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String
#include <list>
#include <iostream>

#include "Audio.h"
#include "InitialTile.h"
#include "BuildableTile.h"
#include "EndTile.h"
#include "PathTile.h"

#include "Space.h" 
#include "Pad.h"


class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void keysToControls(SDL_Event event);
	void update() override;
	void draw() override;

	void mouseToControls(SDL_Event event); // USO DE MOUSE
	
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	int mapWidth;
	int mapHeight;

	InitialTile* initialTile;
	EndTile* endTile;
	list<PathTile*> pathTiles;
	list<BuildableTile*> buildableTiles;

	Space* space;
	int newEnemyTime = 0;

	Background* background;
	list<Enemy*> enemies;
	list<Projectile*> projectiles;
	list<EnemyProjectile*> eProjectiles;

	bool controlContinue = false;
	bool controlShoot = false;

	Actor* backgroundPoints;
	Text* textPoints;
	int points;

	Actor* backgroundLives;
	Text* textLives;
	int lives;

	Actor* backgroundCollectables;
	Text* textCollectables;
	int collectablesObtained;

	Audio* audioBackground;


	// Elementos de interfaz
	Actor* buttonJump;
	Actor* buttonShoot;

	Pad* pad;

	Actor* message;
	bool pause;

};


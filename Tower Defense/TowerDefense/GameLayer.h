#pragma once

#include "Layer.h"
#include "Background.h"

//Enemies
#include "Enemy.h"
#include "BlueEnemy.h"
#include "StandardEnemy.h"

//Towers
#include "Tower.h"
#include "BasicTower.h"
#include "BlastTower.h"
#include "CannonTower.h"
#include "FreezeTower.h"

#include "TowerProjectile.h"

#include "Text.h"
#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String
#include <list>
#include <iostream>

#include "Audio.h"

//Tiles
#include "InitialTile.h"
#include "BuildableTile.h"
#include "EndTile.h"
#include "PathTile.h"

#include "Space.h" 


class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	list<PathTile*> ordenaPathTiles();
	void loadHUD();
	void processControls() override;
	void keysToControls(SDL_Event event);
	void update() override;
	void draw() override;
	Space* space;

	void mouseToControls(SDL_Event event); // USO DE MOUSE
	
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	int mapWidth;
	int mapHeight;

	//Tiles
	InitialTile* initialTile;
	EndTile* endTile;
	list<PathTile*> pathTiles;
	list<BuildableTile*> buildableTiles;

	Background* background;

	//Actors
	list<Enemy*> enemies;
	list<TowerProjectile*> towerProjectiles;
	list<Tower*> towers;

	bool controlContinue = false;
	bool controlShoot = false;

	Actor* backgroundPoints;
	Text* textPoints;
	int points;

	Actor* backgroundLives;
	Text* textLives;
	int lives;

	Audio* audioBackground;

	Text* textRounds;
	Text* textNumberOfRounds;
	int rounds = 0;
	int roundPowerUpAt = 5;
	int timeToNewEnemy = 0;
	int newEnemyTime = 150;

	// Elementos de interfaz
	Actor* buttonBasicTower;
	Actor* buttonCannonTower;
	Actor* buttonFreezeTower;
	Actor* buttonBlastTower;

	//Precios torres
	Text* textPrecioBasic;
	int precioBasic = 50;
	Text* textPrecioCannon;
	int precioCannon = 75;
	Text* textPrecioFreeze;
	int precioFreeze = 80;
	Text* textPrecioBlast;
	int precioBlast = 100;

	BuildableTile* selectedTile;
	void releaseTile();

	Tower* selectedTower;

	void updatePoints(int pointsToAdd);

	Actor* message;
	bool pause;

};


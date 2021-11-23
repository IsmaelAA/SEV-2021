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

#include "Projectile.h"

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
	list<Projectile*> projectiles;
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

	int newEnemyTime = 0;

	// Elementos de interfaz
	Actor* buttonBasicTower;
	Actor* buttonCannonTower;
	Actor* buttonFreezeTower;
	Actor* buttonBlastTower;

	BuildableTile* selectedTile;
	void releasteTile();

	Actor* message;
	bool pause;

};


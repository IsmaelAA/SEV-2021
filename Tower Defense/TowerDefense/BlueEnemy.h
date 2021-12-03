#pragma once
#include "Enemy.h"
#include "Audio.h"
#include <list>
class BlueEnemy : public Enemy
{
public:
	BlueEnemy(float x, float y, list<PathTile*> pathTiles, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	void update();
	int getPoints();
	int getHealthPoints();
	void subHealthPoints(int newHP);
	void impacted(); // Recibe impacto y pone animación de morir

	Animation* aMoving;
	Animation* animation; // Referencia a la animación mostrada
	Animation* aDying;

	list<PathTile*> pathTiles;

	int healthPoints = 2;
	float speed = 4;
	int pointsDrop = 15;
};
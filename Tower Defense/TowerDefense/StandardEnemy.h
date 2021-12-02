#pragma once
#include "Enemy.h"
#include <list>;
class StandardEnemy : public Enemy
{
public:
	StandardEnemy(float x, float y, Game* game);
	StandardEnemy(float x, float y,list<PathTile*> pathTiles, Game* game);
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

	int healthPoints = 5;
	float speed = 1;
	int pointsDrop = 10;
};


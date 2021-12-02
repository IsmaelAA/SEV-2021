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
	void impacted(); // Recibe impacto y pone animaci�n de morir

	Animation* aMoving;
	Animation* animation; // Referencia a la animaci�n mostrada
	Animation* aDying;
	
	list<PathTile*> pathTiles;
	float speed = 1;
	int pointsDrop = 10;
};


#pragma once
#include "Enemy.h"
class StandardEnemy : public Enemy
{
public:
	StandardEnemy(float x, float y, Game* game);
	void draw(float scrollX = 0) override; // Va a sobrescribir
	void update();
	Animation* aMoving;
	Animation* animation; // Referencia a la animaci�n mostrada
	void impacted(); // Recibe impacto y pone animaci�n de morir
	Animation* aDying;
	float vxIntelligence;

	EnemyProjectile* shoot();
};


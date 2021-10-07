#pragma once
#include "Enemy.h"
class StandardEnemy : public Enemy
{
public:
	StandardEnemy(float x, float y, Game* game);
	void draw(float scrollX = 0) override; // Va a sobrescribir
	void update();
	Animation* aMoving;
	Animation* animation; // Referencia a la animación mostrada
	void impacted(); // Recibe impacto y pone animación de morir
	Animation* aDying;
	float vxIntelligence;

	EnemyProjectile* shoot();
};


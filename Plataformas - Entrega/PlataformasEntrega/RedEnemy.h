#pragma once
#include "Enemy.h"
#include "Audio.h"
class RedEnemy : public Enemy
{
public:
	RedEnemy(float x, float y, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	void update();
	Animation* aMoving;
	Animation* animation; // Referencia a la animación mostrada
	void impacted(); // Recibe impacto y pone animación de morir
	Animation* aDying;
	float vxIntelligence;
	
	int orientation;

	EnemyProjectile* shoot();
	Audio* audioShoot;
	int shootCadence = 70;
	int shootTime = 30;
};


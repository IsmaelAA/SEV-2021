#pragma once
#include "Animation.h" 
#include "EnemyProjectile.h" 
#include "Audio.h" 

#include "Enemy.h" 
class StandardEnemy : public Enemy
{
public:
	StandardEnemy(float x, float y, Game* game);
	void draw() override; // Va a sobrescribir
	void update();
	Animation* aMoving;
	Animation* animation; // Referencia a la animación mostrada

	EnemyProjectile* shoot();
	Audio* audioShoot;
	int shootCadence = 70;
	int shootTime = 30;
};


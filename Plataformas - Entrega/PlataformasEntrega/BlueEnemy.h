#pragma once
#include "Enemy.h"
#include "Audio.h"
class BlueEnemy : public Enemy
{
public:
	BlueEnemy(float x, float y, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	void update();

	Animation* aMoving;
	Animation* animation; // Referencia a la animación mostrada

	void impacted(); // Recibe impacto y pone animación de morir
	Animation* aDying;

	EnemyProjectile* shoot();

	int tiempoCiclo = 80;
	int ciclo = 80;
};
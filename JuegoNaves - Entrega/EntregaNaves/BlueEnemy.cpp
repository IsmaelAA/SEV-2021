#include "BlueEnemy.h"


BlueEnemy::BlueEnemy(float x, float y, Game* game)
	: Enemy("res/enemigo_azul.png", x, y, 36, 40, game)
{
	vx = 1;
}

void BlueEnemy::update()
{
	x = x - vx;
}

EnemyProjectile* BlueEnemy::shoot() {
	return NULL;
}

int BlueEnemy::getPoints()
{
	return points;
}

int BlueEnemy::hit() {
	healthPoints--;
	return healthPoints;
}


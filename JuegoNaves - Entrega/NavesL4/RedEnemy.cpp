#include "RedEnemy.h"

RedEnemy::RedEnemy(float x, float y, Game* game)
	: Enemy("res/enemigo_rojo.png", x, y, 36, 40, game)
{
	vx = 2;
	vy = -4;
}

void RedEnemy::update()
{
	x = x - vx;
	y = y + vy;

	if (y <= 0 || y >= HEIGHT){
		vy = -vy;
	}

}
EnemyProjectile* RedEnemy::shoot() {
	return NULL;
}


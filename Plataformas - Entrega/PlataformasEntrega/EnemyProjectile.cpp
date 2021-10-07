#include "EnemyProjectile.h"
EnemyProjectile::EnemyProjectile(float x, float y, Game* game) :
	Actor("res/disparo_enemigo.png", x, y, 20, 20, game) {
	vx = -8;
	vy = -1; // La gravedad inicial es 1
}

void EnemyProjectile::update() {
	vy = vy - 1; // La gravedad suma 1 en cada actualización restamos para anularla 
}
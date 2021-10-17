#include "EnemyProjectile.h"
EnemyProjectile::EnemyProjectile(float x, float y, Game* game) :
	Actor("res/disparo_jugador.png", x, y, 18, 6, game) {
	vx = 6;
	vy = 0; // La gravedad inicial es 1
}

void EnemyProjectile::update() {
	vy = vy - 1; // La gravedad suma 1 en cada actualización restamos para anularla 
}
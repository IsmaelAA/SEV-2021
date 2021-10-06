#include "Projectile.h"

Projectile::Projectile(float x, float y, Game* game) :
	Actor("res/disparo_jugador2.png", x, y, 20, 20, game) {
	vx = 9;
	vy = -1; // La gravedad inicial es 1
}

void Projectile::update() {
	vy = vy - 1; // La gravedad suma 1 en cada actualización restamos para anularla 
}

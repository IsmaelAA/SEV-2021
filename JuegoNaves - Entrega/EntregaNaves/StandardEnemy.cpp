#include "StandardEnemy.h"

StandardEnemy::StandardEnemy(float x, float y, Game* game)
	:Enemy("res/enemigo.png", x, y, 36, 40, game) {

	audioShoot = new Audio("res/efecto_disparo.wav", false);

	vx = 1;

	aMoving = new Animation("res/enemigo_movimiento.png", width, height,
		108, 40, 6, 3, game);
	animation = aMoving;

}


void StandardEnemy::update() {
	// Tiempo de espera de disparo
	if (shootTime > 0) {
		shootTime--;
	}
	// Actualizar la animación
	animation->update();

	vx = -1;
	x = x + vx;
}

void StandardEnemy::draw() {
	animation->draw(x, y);
}

EnemyProjectile* StandardEnemy::shoot() {
	if (shootTime == 0 && this->isInRender()) {
		audioShoot->play();
		shootTime = shootCadence;
		return new EnemyProjectile(x, y, game);
	}
	else {
		return NULL;
	}
}


int StandardEnemy::getPoints() {
	return points;
}

int StandardEnemy::hit() {
	healthPoints--;
	return healthPoints;
}


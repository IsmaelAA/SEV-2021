#include "RedEnemy.h"

RedEnemy::RedEnemy(float x, float y, Game* game)
	: Enemy("res/enemigo_rojo.png", x, y, 36, 40, game) {

	vxIntelligence = -2;
	vx = vxIntelligence;

	state = game->stateMoving;
	orientation = game->orientationLeft;

	aDying = new Animation("res/enemigo_morir_rojo.png", width, height,
		280, 40, 6, 8, false, game);

	aMoving = new Animation("res/enemigo_movimiento_rojo.png", width, height,
		108, 40, 6, 3, true, game);

	audioShoot = new Audio("res/efecto_disparo.wav", false);


	animation = aMoving;

}

void RedEnemy::update() {
	shootTime--;
	// Actualizar la animación
	bool endAnimation = animation->update();

	// Establecer orientación
	if (vx > 0) {
		orientation = game->orientationRight;
	}
	if (vx < 0) {
		orientation = game->orientationLeft;
	}

	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		// Estaba muriendo
		if (state == game->stateDying) {
			state = game->stateDead;
		}
	}

	if (state == game->stateMoving) {
		animation = aMoving;
	}
	if (state == game->stateDying) {
		animation = aDying;
	}

	// Establecer velocidad
	if (state != game->stateDying) {
		// no está muerto y se ha quedado parado
		if (vx == 0) {
			vxIntelligence = vxIntelligence * -1;
			vx = vxIntelligence;
		}

		if (outRight) {
			// mover hacia la izquierda vx tiene que ser negativa
			if (vxIntelligence > 0) {
				vxIntelligence = vxIntelligence * -1;
			}
			vx = vxIntelligence;
		}
		if (outLeft) {
			// mover hacia la derecha vx tiene que ser positiva
			if (vxIntelligence < 0) {
				vxIntelligence = vxIntelligence * -1;
			}
			vx = vxIntelligence;
		}

	}
	else {
		vx = 0;
	}


}

void RedEnemy::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

void RedEnemy::impacted() {
	if (state != game->stateDying) {
		shootTime = 1000;// que no dispare cuando esta muriendo.
		state = game->stateDying;
	}
}

EnemyProjectile* RedEnemy::shoot() {
	if (shootTime < 0) {
		shootTime = shootCadence;

		audioShoot->play();
		EnemyProjectile* projectile = new EnemyProjectile(x, y, game);
		if (orientation == game->orientationLeft) {
			projectile->vx = projectile->vx * -1; // Invertir
		}
		return projectile;


	}
	return NULL;
}
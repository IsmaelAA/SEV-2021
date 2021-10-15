#include "BlueEnemy.h"

BlueEnemy::BlueEnemy(float x, float y, Game* game)
	: Enemy("res/enemigo_azul.png", x, y, 36, 40, game) {

	vxIntelligence = -1;
	vx = vxIntelligence;

	state = game->stateMoving;

	aDying = new Animation("res/enemigo_morir_azul.png", width, height,
		280, 40, 6, 8, false, game);

	aMoving = new Animation("res/enemigo_movimiento_azul.png", width, height,
		108, 40, 6, 3, true, game);

	animation = aMoving;

	vy = 0;

}

void BlueEnemy::update() {
	vy = vy - 1; // La gravedad suma 1 en cada actualización restamos para anularla 
	// Actualizar la animación
	bool endAnimation = animation->update();

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

void BlueEnemy::draw(float scrollX) {
	animation->draw(x - scrollX, y);
}

void BlueEnemy::impacted() {
	if (state != game->stateDying) {
		state = game->stateDying;
	}
}

EnemyProjectile* BlueEnemy::shoot()
{
	return NULL;
}
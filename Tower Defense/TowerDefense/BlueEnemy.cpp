#include "BlueEnemy.h"

BlueEnemy::BlueEnemy(float x, float y, Game* game)
	: Enemy("res/enemigo_azul.png", x, y, 36, 40, game) {

	state = game->stateMoving;

	aDying = new Animation("res/enemigo_morir_azul.png", width, height,
		280, 40, 6, 8, false, game);

	aMoving = new Animation("res/enemigo_movimiento_azul.png", width, height,
		108, 40, 6, 3, true, game);

	animation = aMoving;

	vx = 0;
	vy = 0;
}

void BlueEnemy::update() {
	tiempoCiclo--;
	// Divido en 4 partes un ciclo

	if (tiempoCiclo < ciclo * 0.25) {
		// Diagonal superior derecha
		vy = -2;
		vx = -1;
	}
	else if (tiempoCiclo < ciclo * 0.5) {
		// Diagonal superior izquierda
		vy = -2;
		vx = 1;
	}
	else if (tiempoCiclo < ciclo * 0.75) {
		// Diagonal inferior izquierda
		vy = 0;
		vx = 1;
	}
	else if (tiempoCiclo < ciclo) {
		// Diagonal inferior derecha
		vy = 0;
		vx = -1;
	}

	// Si tiempo ciclo menor que 0 se resetea
	if (tiempoCiclo < 0)
		tiempoCiclo = ciclo;

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

}

void BlueEnemy::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

void BlueEnemy::impacted() {
	if (state != game->stateDying) {
		state = game->stateDying;
	}
}
#include "BlueEnemy.h"

BlueEnemy::BlueEnemy(float x, float y, list<PathTile*> pathTiles, Game* game) : Enemy("res/basic_tower.png", x, y, 40, 40, game)
{
	this->pathTiles = pathTiles;

	vx = this->speed;

	state = game->stateMoving;

	aDying = new Animation("res/enemigo_morir_azul.png", width, height,
		160, 40, 6, 4, false, game);

	aMoving = new Animation("res/enemigo_movimiento_azul.png", width, height,
		160, 40, 6, 4, true, game);

	animation = aMoving;
}


void BlueEnemy::update() {
	// Actualizar la animacion
	bool endAnimation = animation->update();

	// Acabo la animacion, no sabemos cual
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

	if (state != game->stateDying) {
		if (!pathTiles.empty()) {
			PathTile* firstTile = pathTiles.front();

			if (firstTile->x < this->x)
				vx = -speed;
			else if (firstTile->x > this->x)
				vx = speed;

			if (firstTile->y < this->y)
				vy = -speed;
			else if (firstTile->y > this->y)
				vy = speed;

			if (firstTile->x == this->x)
				vx = 0;
			else if (firstTile->y == this->y)
				vy = 0;

			if (firstTile->containsPoint(this->x, this->y)) {
				pathTiles.remove(firstTile);
			}
		}
	}
	else {
		vx = 0;
		vy = 0;
	}

}

int BlueEnemy::getPoints()
{
	return this->pointsDrop;
}

int BlueEnemy::getHealthPoints()
{
	return healthPoints;
}

void BlueEnemy::subHealthPoints(int newHP)
{
	this->healthPoints -= newHP;
}

void BlueEnemy::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

void BlueEnemy::impacted() {
	if (state != game->stateDying) {
		state = game->stateDying;
	}

}
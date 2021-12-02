#include "StandardEnemy.h"

StandardEnemy::StandardEnemy(float x, float y, Game* game)
	: Enemy("res/enemigo.png", x, y, 36, 40, game) {

	
	vx = this->speed;

	state = game->stateMoving;

	aDying = new Animation("res/enemigo_morir.png", width, height,
		280, 40, 6, 8, false, game);

	aMoving = new Animation("res/enemigo_movimiento.png", width, height,
		108, 40, 6, 3, true, game);

	animation = aMoving;

}

StandardEnemy::StandardEnemy(float x, float y, list<PathTile*> pathTiles, Game* game) : Enemy("res/enemigo.png", x, y, 36, 40, game)
{
	this->pathTiles = pathTiles;

	vx = this->speed;

	state = game->stateMoving;

	aDying = new Animation("res/enemigo_morir.png", width, height,
		280, 40, 6, 8, false, game);

	aMoving = new Animation("res/enemigo_movimiento.png", width, height,
		108, 40, 6, 3, true, game);

	animation = aMoving;
}


void StandardEnemy::update() {
	// Actualizar la animación
	bool endAnimation = animation->update();
	
	if (!pathTiles.empty()) {
		PathTile* firstTile = pathTiles.front();

		if (firstTile->x < this->x)
			vx = -speed;
		if (firstTile->x > this->x)
			vx = speed;
		if (firstTile->x == this->x)
			vx = 0;

		if (firstTile->y < this->y)
			vy = -speed;
		if (firstTile->y > this->y)
			vy = speed;
		if (firstTile->y == this->y)
			vy = 0;

		if (firstTile->containsPoint(this->x, this->y)) {
			pathTiles.remove(firstTile);
		}
	}
		
}

int StandardEnemy::getPoints()
{
	return this->pointsDrop;
}

int StandardEnemy::getHealthPoints()
{
	return healthPoints;
}

void StandardEnemy::subHealthPoints(int newHP)
{
	this->healthPoints -= newHP;
}

void StandardEnemy::draw(float scrollX, float scrollY ) {
	animation->draw(x - scrollX, y - scrollY);
}

void StandardEnemy::impacted() {
	if (state != game->stateDying) {
		state = game->stateDying;
	
	}
	
}


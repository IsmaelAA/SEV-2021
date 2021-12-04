#include "FreezeProjectile.h"

FreezeProjectile::FreezeProjectile(float x, float y, int projectileArea, float slowRatio, Game* game)
	: TowerProjectile("res/freeze_projectile.png", x, y, projectileArea, projectileArea, 200, 200, game) {
		{
			this->state = game->stateMoving;
			this-> projectileArea = projectileArea;
			this-> slowRatio = slowRatio;
		}
}
void FreezeProjectile::update()
{
	timeToExpire--;
}

void FreezeProjectile::hit(Enemy* enemy)
{
	// La velocidad minima que puede tener un enemigo es 1
	if (enemy->vx / slowRatio >= 1)
		enemy->vx /= slowRatio;
	
	if (enemy->vy / slowRatio >= 1)
		enemy->vy /= slowRatio;
}

int FreezeProjectile::getTimeToExpire()
{
	return timeToExpire;
}
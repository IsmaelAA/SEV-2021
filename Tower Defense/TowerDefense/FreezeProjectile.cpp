#include "FreezeProjectile.h"

FreezeProjectile::FreezeProjectile(float x, float y, int projectileArea, float slowRatio, Game* game)
	: TowerProjectile("res/freeze_projectile.png", x, y, projectileArea, projectileArea, 200, 200, game) {
		{
			this-> projectileArea = projectileArea;
			this-> slowRatio = slowRatio;
		}
}
bool FreezeProjectile::update()
{
	return true;
}

bool FreezeProjectile::hit(Enemy* enemy)
{
	if (enemy->vx / slowRatio >= 1)
		enemy->vx /= slowRatio;
	if (enemy->vy / slowRatio >= 1)
		enemy->vy /= slowRatio;
	return false;
}

	

int FreezeProjectile::getTimeToExpire()
{
	return 10;
}
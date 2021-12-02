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

void FreezeProjectile::hit(Enemy* enemy)
{
	enemy->vx /=slowRatio;
	enemy->vy /=slowRatio;
}

int FreezeProjectile::getTimeToExpire()
{
	return 10;
}
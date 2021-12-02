#include "FreezeTower.h"
FreezeTower::FreezeTower(float x, float y, Game* game)
	: Tower("res/freeze_tower.png", x, y, 40, 40, game) {
}
void FreezeTower::update()
{
}

TowerProjectile* FreezeTower::shoot(Enemy* enemy)
{
	if (!isActive) {
		isActive = true;
		return new FreezeProjectile( x, y, (range - 1) * 80 + 40, slowRatio, game);
	}
	else {
		return NULL;
	}
}

int FreezeTower::getRange()
{
	return range;
}

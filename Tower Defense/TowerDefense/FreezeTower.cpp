#include "FreezeTower.h"
FreezeTower::FreezeTower(float x, float y, Game* game)
	: Tower("res/freeze_tower.png", x, y, 40, 40, game) {
}
void FreezeTower::update()
{
	if (shootTime > 0) {
		shootTime--;
	}
}

TowerProjectile* FreezeTower::shoot(Enemy* enemy)
{
	if (shootTime <=0) {
		shootTime = attackSpeed;
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

void FreezeTower::upgrade()
{
	this->range++;
	this->slowRatio+=0.5;
}
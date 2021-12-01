#include "FreezeTower.h"
FreezeTower::FreezeTower(float x, float y, Game* game)
	: Tower("res/freeze_tower.png", x, y, 40, 40, game) {
}


void FreezeTower::update()
{
}

TowerProjectile* FreezeTower::shoot(Enemy* e)
{
	return nullptr;
}

int FreezeTower::getRange()
{
	return range;
}

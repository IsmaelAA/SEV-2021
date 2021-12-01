#include "CannonTower.h"
CannonTower::CannonTower(float x, float y, Game* game)
	: Tower("res/cannon_tower.png", x, y, 40, 40, game) {
}


void CannonTower::update()
{
}

TowerProjectile* CannonTower::shoot(Enemy* e)
{
	return nullptr;
}

int CannonTower::getRange()
{
	return range;
}

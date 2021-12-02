#include "CannonTower.h"
CannonTower::CannonTower(float x, float y, Game* game)
	: Tower("res/cannon_tower.png", x, y, 40, 40, game) {
}


void CannonTower::update()
{
	if (shootTime > 0) {
		shootTime--;
	}
}

TowerProjectile* CannonTower::shoot(Enemy* enemy)
{
	if (shootTime <= 0) {
		shootTime = attackSpeed;
		return new CannonProjectile(enemy,x, y, projectileSpeed, damage, game);
	}
	else {
		return NULL;
	}
}

int CannonTower::getRange()
{
	return range;
}

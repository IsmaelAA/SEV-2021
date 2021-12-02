#include "BlastTower.h"
BlastTower::BlastTower(float x, float y, Game* game)
	: Tower("res/blast_tower.png", x, y, 40, 40, game) {
}

void BlastTower::update()
{
	if (shootTime > 0) {
		shootTime--;
	}
}

TowerProjectile* BlastTower::shoot(Enemy* enemy)
{
	if (shootTime <= 0) {
		shootTime = attackSpeed;
		//return new BlastProjectile(enemy,x, y, projectileSpeed, damage, game);
	}
	else {
		return NULL;
	}
}

int BlastTower::getRange()
{
	return range;
}

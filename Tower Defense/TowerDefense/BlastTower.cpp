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
		return new BlastProjectile(x, y, (range - 1) * 80 + 40,damage, game);
	}
	else {
		return NULL;
	}
}

int BlastTower::getRange()
{
	return range;
}

void BlastTower::upgrade()
{
	this->range++;
	this->attackSpeed -= 5;
	this->damage++;
}

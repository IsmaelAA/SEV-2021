#include "BlastTower.h"
BlastTower::BlastTower(float x, float y, Game* game)
	: Tower("res/blast_tower.png", x, y, 40, 40, game) {
}

TowerProjectile* BlastTower::shoot(Enemy* enemy)
{
	return nullptr;
}

int BlastTower::getRange()
{
	return range;
}


void BlastTower::update()
{
}
#include "BlastTower.h"
BlastTower::BlastTower(float x, float y, Game* game)
	: Tower("res/blast_tower.png", x, y, 40, 40, game) {
}

int BlastTower::getRange()
{
	return range;
}


void BlastTower::update()
{
}
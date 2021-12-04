#pragma once
#include "Tower.h"
#include "BlastProjectile.h"
class BlastTower : public Tower
{
public:
	BlastTower(float x, float y, Game* game);
	TowerProjectile* shoot(Enemy* enemy);
	int getRange();
	void update();
	void upgrade();

	//Stats
	int attackSpeed = 180;
	int shootTime = 0;

	int damage = 1;
	int range = 2;
};

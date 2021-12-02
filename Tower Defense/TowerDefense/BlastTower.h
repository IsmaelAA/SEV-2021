#pragma once
#include "Tower.h"
class BlastTower : public Tower
{
public:
	BlastTower(float x, float y, Game* game);
	TowerProjectile* shoot(Enemy* enemy);
	int getRange();
	void update();


	//Stats
	int attackSpeed = 20;
	int shootTime = 0;
	int projectileSpeed = 1;
	int damage = 2;
	int range = 2;
};

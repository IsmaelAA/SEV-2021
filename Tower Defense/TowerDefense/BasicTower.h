#pragma once
#include "Tower.h"
#include "BasicProjectile.h"
class BasicTower : public Tower
{
public:
	BasicTower(float x, float y, Game* game);
	void update();
	TowerProjectile* shoot(Enemy* enemy);
	int getRange();
	void upgrade();

	//Stats
	int attackSpeed = 20;
	int shootTime = 0;
	int projectileSpeed = 3;
	int damage = 1;
	int range = 3;
};



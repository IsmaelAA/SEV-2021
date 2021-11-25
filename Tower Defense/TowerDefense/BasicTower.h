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

	//Stats
	int attackSpeed = 30;
	int shootTime = 0;
	int projectileSpeed = 2;
	int damage = 5;
	int range = 3;
};



#pragma once
#include "Tower.h"
#include "CannonProjectile.h"
class CannonTower :
    public Tower
{

public:
	CannonTower(float x, float y, Game* game);
	void update();
	TowerProjectile* shoot(Enemy* enemy);
	int getRange();


	//Stats
	int shootTime = 0;
	int attackSpeed = 50;
	int projectileSpeed = 2;
	int damage = 5;
	int range = 3;
};


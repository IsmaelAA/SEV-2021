#pragma once
#include "Tower.h"
#include "FreezeProjectile.h"
class FreezeTower :
    public Tower
{

public:
	FreezeTower(float x, float y, Game* game);
	void update();
	TowerProjectile* shoot(Enemy* e);
	int getRange();

	//Stats
	int attackSpeed = 1;
	int shootTime = 0;
	float slowRatio = 0.5;
	int range = 4;
};


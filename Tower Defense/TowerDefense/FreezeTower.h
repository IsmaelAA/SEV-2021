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
	bool isActive = false;
	float slowRatio = 2;
	int range = 3;
};


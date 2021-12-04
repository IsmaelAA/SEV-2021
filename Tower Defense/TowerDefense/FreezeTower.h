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
	void upgrade();

	//Stats
	int shootTime = 0;
	int attackSpeed = 100;
	float slowRatio = 2; // Divide la velocidad del enemigo en este numero, cuanto mayor sea este numero mayor slow.
	int range = 3;
};


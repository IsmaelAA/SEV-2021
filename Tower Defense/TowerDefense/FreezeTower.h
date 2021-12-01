#pragma once
#include "Tower.h"
class FreezeTower :
    public Tower
{

public:
	FreezeTower(float x, float y, Game* game);
	void update();
	TowerProjectile* shoot(Enemy* e);
	int getRange();

	//Stats
	int attackSpeed = 5;
	int projectileSpeed = 1;
	int damage = 5;
	int range = 4;
};


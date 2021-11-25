#pragma once
#include "Tower.h"
class BlastTower :
    public Tower
{

public:
	BlastTower(float x, float y, Game* game);
	TowerProjectile* shoot();
	int getRange();
	void update();

	//Stats
	int attackSpeed = 5;
	int projectileSpeed = 1;
	int damage = 5;
	int range = 2;
};


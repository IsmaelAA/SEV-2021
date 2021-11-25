#pragma once
#include "Tower.h"
class CannonTower :
    public Tower
{

public:
	CannonTower(float x, float y, Game* game);
	void update();
	int getRange();

	//Stats
	int attackSpeed = 5;
	int projectileSpeed = 1;
	int damage = 5;
	int range = 5;
};


#pragma once
#include "TowerProjectile.h"
class FreezeProjectile :
    public TowerProjectile
{
public:
	FreezeProjectile(float x, float y, int projectileArea, float slowRatio, Game* game);
	bool update();
	void hit(Enemy* enemy);
	int getTimeToExpire();

	int projectileArea;
	int slowRatio;
	int timeToExpire = 0;
};


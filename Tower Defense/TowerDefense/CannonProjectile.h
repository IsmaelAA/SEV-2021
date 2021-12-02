#pragma once
#include "TowerProjectile.h"

class CannonProjectile : public TowerProjectile
{
public:
	CannonProjectile(Enemy* enemy , float x, float y, int projectileSpeed, int projectileDamage, Game* game);
	bool update();
	void hit(Enemy* enemy);
	int getTimeToExpire();

	int timeToExpire = 0;
};



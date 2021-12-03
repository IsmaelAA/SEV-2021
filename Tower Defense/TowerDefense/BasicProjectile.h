#pragma once
#include "TowerProjectile.h"
class BasicProjectile : public TowerProjectile
{
public:
	BasicProjectile(Enemy* enemy,float x, float y,int projectileSpeed,int projectileDamage, Game* game);
	bool update();
	bool hit(Enemy* enemy);
	int getTimeToExpire();

	int timeToExpire = 100;

};


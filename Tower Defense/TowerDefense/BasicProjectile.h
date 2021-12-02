#pragma once
#include "TowerProjectile.h"
class BasicProjectile : public TowerProjectile
{
public:
	BasicProjectile(float x, float y,int projectileSpeed,int projectileDamage, Game* game);
	void update(Enemy* enemy);
};


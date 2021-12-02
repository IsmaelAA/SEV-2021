#pragma once
#include "Actor.h"
#include "Enemy.h"
class TowerProjectile : public Actor
{
public:
	TowerProjectile(string filename, float x, float y, int width, int height, Game* game);
	virtual void update(Enemy* enemy) = 0;
	int projectileDamage;
	int projectileSpeed;
};


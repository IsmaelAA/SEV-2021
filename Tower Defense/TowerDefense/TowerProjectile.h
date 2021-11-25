#pragma once
#include "Actor.h"
class TowerProjectile : public Actor
{
public:
	TowerProjectile(string filename, float x, float y, int width, int height, Game* game);
	virtual void update() = 0;
	int projectileDamage;
	int projectileSpeed;
};


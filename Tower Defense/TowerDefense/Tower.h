#pragma once
#include "Actor.h"
#include "Enemy.h"
#include "TowerProjectile.h"
class Tower : public Actor
{
public:
	Tower(string filename, float x, float y, int width, int height, Game* game);
	virtual void update() = 0;
	virtual TowerProjectile* shoot(Enemy* enemy) = 0;
	virtual int getRange() = 0;

	bool hasInRange(Enemy* enemy);

	//Stats
	int attackSpeed = 0;
	int projectileSpeed = 0;
	int damage = 0;
	int range = 0;

	int state = 0;
};

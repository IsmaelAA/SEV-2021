#pragma once
#include "Actor.h"
#include "Enemy.h"
class TowerProjectile : public Actor
{
public:
	TowerProjectile(string filename, float x, float y, int width, int height, Game* game);
	TowerProjectile(string filename, float x, float y, int width, int height,int fileWidth, int fileHeight, Game* game);
	virtual void update() = 0;
	virtual void hit(Enemy* enemy) = 0;
	virtual int getTimeToExpire() = 0;


	int state = 0;
	Enemy* targetEnemy;
	int projectileDamage;
	int projectileSpeed;
};


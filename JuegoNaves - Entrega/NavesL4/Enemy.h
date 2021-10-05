#pragma once

#include "Actor.h"
#include "EnemyProjectile.h" 
class Enemy : public Actor
{
public:
	Enemy(string filename, float x, float y, int width, int height, Game* game);
	virtual void update() = 0;
	virtual EnemyProjectile* shoot() = 0;
	virtual int getPoints() = 0;
	virtual int hit() = 0;
};

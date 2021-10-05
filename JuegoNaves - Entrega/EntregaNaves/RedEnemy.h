#pragma once

#include "Actor.h"
#include "Enemy.h" 
#include <math.h>

class RedEnemy : public Enemy
{
public:
	RedEnemy(float x, float y, Game* game);
	void update();
	EnemyProjectile* shoot();

	int points = 1;
	int getPoints();

	int healthPoints = 1;
	int hit();
};


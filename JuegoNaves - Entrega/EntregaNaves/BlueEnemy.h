#pragma once

#include "Actor.h"
#include "Enemy.h" 
#include <math.h>

class BlueEnemy : public Enemy
{
public:
	BlueEnemy(float x, float y, Game* game);
	void update();
	EnemyProjectile* shoot();

	int points = 5;
	int getPoints();

	int healthPoints = 3;
	int hit();
};


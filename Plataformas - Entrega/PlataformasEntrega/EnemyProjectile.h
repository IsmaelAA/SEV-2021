#pragma once
#include "Actor.h"
class EnemyProjectile : public Actor
{
public:
	EnemyProjectile(float x, float y, Game* game);
	void update();
};


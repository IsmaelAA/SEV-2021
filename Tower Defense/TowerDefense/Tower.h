#pragma once
#include "Actor.h"
class Tower : public Actor
{
public:
	Tower(string filename, float x, float y, int width, int height, Game* game);
	virtual void update() = 0;

	//Stats
	int attackSpeed = 0;
	int projectileSpeed = 0;
	int damage = 0;
	int range = 0;

	int state = 0;
};

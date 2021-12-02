#pragma once

#include "Actor.h"
#include "Animation.h" 
#include "PathTile.h"
class Enemy : public Actor
{
public:
	Enemy(string filename, float x, float y, int width, int height, Game* game);
	virtual void update() = 0;
	virtual void impacted() = 0;
	virtual int getPoints() = 0;

	int state = 0;
	int pointsDrop = 0;
};

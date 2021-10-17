#pragma once
#include "Actor.h"
class FakeTile : public Actor
{
public:
	FakeTile(float x, float y, Game* game);
	bool isTime();
	void update();
	bool isOn = false;
	int tiempoDestruccion = 15;
};


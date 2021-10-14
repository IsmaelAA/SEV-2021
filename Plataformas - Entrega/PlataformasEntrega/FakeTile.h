#pragma once
#include "Actor.h"
class FakeTile : public Actor
{
public:
	FakeTile(float x, float y, Game* game);
	bool isTime();
	int tiempoDestruccion = 30;
	int cadencia = 30;
};


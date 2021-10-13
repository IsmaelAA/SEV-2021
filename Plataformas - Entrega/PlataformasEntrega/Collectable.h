#pragma once
#include "Actor.h"
#include "Animation.h" 
class Collectable : public Actor
{
public:
	Collectable(float x, float y, Game* game);
	void update();
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir

	Animation* animation; // Referencia a la animación mostrada
};


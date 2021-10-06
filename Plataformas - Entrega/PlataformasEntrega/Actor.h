#pragma once

#include "Game.h"

class Actor
{
public:
	Actor(string filename, float x, float y, int width, int height, Game* game);
	virtual void draw(float scrollx = 0);
	bool isOverlap(Actor* actor);
	bool isInRender(float scrollX = 0);
	bool containsPoint(int pointX, int pointY); // contiene punto
	bool collisionDown = false;
	bool outRight;
	bool outLeft;
	
	SDL_Texture* texture;
	int x;
	int y;
	float vx = 0;
	float vy = 0;
	int width;
	int height;
	int fileWidth;
	int fileHeight;
	bool clicked; // Está pulsado
	Game* game; // referencia al juego
};


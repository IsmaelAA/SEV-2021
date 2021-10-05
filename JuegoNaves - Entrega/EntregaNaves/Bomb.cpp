#include "Bomb.h"
#include "Audio.h"
Bomb::Bomb(float x, float y, Game* game)
	: Actor("res/bomb.png", x, y, 32, 40, game) {
	audioBomb = new Audio("res/efecto_explosion.wav", false);
	vx = -1;
}


void Bomb::update() {
	x = x + vx;
}

void Bomb::explote() {
	audioBomb->play();
}
#include "FakeTile.h"

FakeTile::FakeTile(float x, float y, Game* game) :
	Actor("res/bloque_fondo_muro.png", x, y, 40, 32, game)
{

}

bool FakeTile::isTime()
{
	if (tiempoDestruccion < 0) {
		return true;
	}
	tiempoDestruccion--;
	return false;
}

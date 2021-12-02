#include "TowerProjectile.h"

TowerProjectile::TowerProjectile(string filename, float x, float y, int width, int height, Game* game)
	: Actor(filename, x, y, width, height, game) {
}

TowerProjectile::TowerProjectile(string filename, float x, float y, int width, int height, int fileWidth, int fileHeight, Game* game)
	: Actor(filename, x, y, width, height, fileWidth, fileHeight, game) {
}


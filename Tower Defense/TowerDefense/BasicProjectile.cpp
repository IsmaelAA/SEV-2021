#include "BasicProjectile.h"

BasicProjectile::BasicProjectile(float x, float y, int projectileSpeed, int projectileDamage, Game* game)
	: TowerProjectile("res/basic_projectile.png", x, y, 20, 20, game) {
		{
			this->projectileSpeed = projectileSpeed;
			this->projectileDamage = projectileDamage;
		}
}
void BasicProjectile::update()
{
	vx = projectileSpeed;
}

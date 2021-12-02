#include "BasicProjectile.h"

BasicProjectile::BasicProjectile(float x, float y, int projectileSpeed, int projectileDamage, Game* game)
	: TowerProjectile("res/basic_projectile.png", x, y, 20, 20, game) {
		{
			this->projectileSpeed = projectileSpeed;
			this->projectileDamage = projectileDamage;
		}
}
void BasicProjectile::update(Enemy* enemy)
{

	if (enemy != NULL) {
		if (enemy->x < this->x)
			vx = -projectileSpeed;
		if (enemy->x > this->x)
			vx = projectileSpeed;
		if (enemy->x == this->x)
			vx = 0;
		if (enemy->y < this->y)
			vy = -projectileSpeed;
		if (enemy->y > this->y)
			vy = projectileSpeed;
		if (enemy->y == this->y)
			vy = 0;
	}
}

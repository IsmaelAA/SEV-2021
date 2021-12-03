#include "BasicProjectile.h"

BasicProjectile::BasicProjectile(Enemy* enemy,float x, float y, int projectileSpeed, int projectileDamage, Game* game)
	: TowerProjectile("res/basic_projectile.png", x, y, 10, 10,20,20, game) {
		{
			this->targetEnemy = enemy;
			this->projectileSpeed = projectileSpeed;
			this->projectileDamage = projectileDamage;
		}
}
bool BasicProjectile::update()
{
	timeToExpire--;

	if (targetEnemy->isInRender()) {
		if (targetEnemy->x < this->x)
			vx = -projectileSpeed;
		if (targetEnemy->x > this->x)
			vx = projectileSpeed;
		if (targetEnemy->x == this->x)
			vx = 0;
		if (targetEnemy->y < this->y)
			vy = -projectileSpeed;
		if (targetEnemy->y > this->y)
			vy = projectileSpeed;
		if (targetEnemy->y == this->y)
			vy = 0;
		return true;
	}else
		return false;
}

bool BasicProjectile::hit(Enemy* enemy)
{
	enemy->subHealthPoints(this->projectileDamage);
	return true;
}

int BasicProjectile::getTimeToExpire()
{
	return timeToExpire;
}

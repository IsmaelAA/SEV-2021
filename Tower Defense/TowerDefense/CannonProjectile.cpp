#include "CannonProjectile.h"
CannonProjectile::CannonProjectile(Enemy* enemy,float x, float y, int projectileSpeed, int projectileDamage, Game* game)
	: TowerProjectile("res/cannon_projectile.png", x, y, 15, 15, 20, 20, game) {
		{
			this->targetEnemy = enemy;
			this->projectileSpeed = projectileSpeed;
			this->projectileDamage = projectileDamage;
		}
}

bool CannonProjectile::update()
{
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
	}
	else
		return false;
}

void CannonProjectile::hit(Enemy* enemy)
{
	enemy->subHealthPoints(this->projectileDamage);
}

int CannonProjectile::getTimeToExpire()
{
	return timeToExpire;
}

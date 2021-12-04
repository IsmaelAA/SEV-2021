#include "CannonProjectile.h"
CannonProjectile::CannonProjectile(Enemy* enemy,float x, float y, int projectileSpeed, int projectileDamage, Game* game)
	: TowerProjectile("res/cannon_projectile.png", x, y, 15, 15, 20, 20, game) {
		{
			this->state = game->stateMoving;
			this->targetEnemy = enemy;
			this->projectileSpeed = projectileSpeed;
			this->projectileDamage = projectileDamage;
		}
}

void CannonProjectile::update()
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
	}
	else
		state = game->stateDead;
}

void CannonProjectile::hit(Enemy* enemy)
{
	enemy->subHealthPoints(this->projectileDamage);
	
	state = game->stateDead;
}

int CannonProjectile::getTimeToExpire()
{
	return timeToExpire;
}

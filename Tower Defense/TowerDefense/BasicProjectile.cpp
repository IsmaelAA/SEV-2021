#include "BasicProjectile.h"

BasicProjectile::BasicProjectile(Enemy* enemy,float x, float y, int projectileSpeed, int projectileDamage, Game* game)
	: TowerProjectile("res/basic_projectile.png", x, y, 10, 10,20,20, game) {
		{
			this->state = game->stateMoving;
			this->targetEnemy = enemy;
			this->projectileSpeed = projectileSpeed;
			this->projectileDamage = projectileDamage;
		}
}
void BasicProjectile::update()
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

void BasicProjectile::hit(Enemy* enemy)
{
	enemy->subHealthPoints(this->projectileDamage);
	state = game->stateDead;
}

int BasicProjectile::getTimeToExpire()
{
	return timeToExpire;
}

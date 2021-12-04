#include "BasicTower.h"
BasicTower::BasicTower(float x, float y, Game* game)
	: Tower("res/basic_tower.png", x, y, 40, 40, game) {
}


void BasicTower::update()
{
	if (shootTime > 0) {
		shootTime--;
	}
}

TowerProjectile* BasicTower::shoot(Enemy* enemy)
{
	if(shootTime<=0){
		shootTime = attackSpeed;
		return new BasicProjectile(enemy, x,y,projectileSpeed,damage,game);
	}
	else {
		return NULL;
	}
}

int BasicTower::getRange()
{
	return range;
}

void BasicTower::upgrade()
{
	 this->attackSpeed -= 5;
	 this->damage++ ;
}

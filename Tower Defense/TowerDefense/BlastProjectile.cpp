#include "BlastProjectile.h"
BlastProjectile::BlastProjectile(float x, float y, int projectileArea,int projectileDamage, Game* game)
	: TowerProjectile("res/blast_projectile.png", x, y, projectileArea, projectileArea, 200, 200, game) {
		{
			this->state = game->stateMoving;
			this->projectileDamage = projectileDamage;
			this->projectileArea = projectileArea;
		}
}
void BlastProjectile::update()
{
	// tendra 4 intervalos(60%15) de activacion, esto lo hago porque si no estaria en cada frame haciendo daño a los enemigos, lo que quitaria la gracia del juego.
	if (timeToExpire % 15 == 0 ) {
		isActive = true;
	}
	else
		isActive = false;

	timeToExpire--;
	
}

void BlastProjectile::hit(Enemy* enemy)
{
	if (isActive) {
		enemy->subHealthPoints(this->projectileDamage);
		
	}
	
}

int BlastProjectile::getTimeToExpire()
{
	return timeToExpire;
}
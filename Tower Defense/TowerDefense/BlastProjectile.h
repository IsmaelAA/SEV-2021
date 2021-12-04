#pragma once
#include "TowerProjectile.h"
class BlastProjectile :
    public TowerProjectile
{
public:
	BlastProjectile(float x, float y, int projectileArea,int projectileDamage, Game* game);
	void update();
	void hit(Enemy* enemy);
	int getTimeToExpire();

	bool isActive = false;
	int projectileArea;
	
	// El tiempo que permanece activa el area de efecto del blast
	int timeToExpire = 60;

};


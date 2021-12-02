#include "Tower.h"
#include "Math.h"
Tower::Tower(string filename, float x, float y, int width, int height, Game* game) 
	: Actor(filename, x, y, width, height, game) {
}

bool Tower::hasInRange(Enemy* enemy)
{
	int enemyX = enemy->x;
	int enemyY = enemy->y;
	float radius = (this->getRange() - 1) * 40+20;
	
	// (xp−xc)^2+(yp−yc)^2 
	float distance = pow(enemyX - this->x, 2) + pow(enemyY - this->y, 2);
	
	// d^2 <= r^2
		if (distance <= pow(radius, 2)) {
			return true;
		}
	return false;
}

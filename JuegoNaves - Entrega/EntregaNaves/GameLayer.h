#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"

#include "Enemy.h"
#include "StandardEnemy.h"
#include "RedEnemy.h"
#include "BlueEnemy.h"
#include "Projectile.h"
#include "EnemyProjectile.h"
#include "Text.h"

#include "Coin.h"
#include "Bomb.h"
#include "Audio.h" 

#include <list>


class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;

	void keysToControls(SDL_Event event);
	int newEnemyTime = 0;
	int newRedEnemyTime = 0;
	int newBlueEnemyTime = 0;

	Player* player;
	Background* background;
	list<Enemy*> enemies;
	list<Projectile*> projectiles;
	list<EnemyProjectile*> enemyProjectiles;

	bool controlShoot = false;
	int controlMoveY = 0;
	int controlMoveX = 0;

	Actor* backgroundPoints;
	Actor* backgroundHealth;
	Text* textHealth;
	Text* textPoints;
	int points;

	Audio* audioBackground;

	int newCoinTime = 0;
	list<Coin*> coins;

	int newBombTime = 500;
	list<Bomb*> bombs;
};


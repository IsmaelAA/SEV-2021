#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"

#include "Enemy.h"
#include "Projectile.h"
#include "Text.h"
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

	Player* player;
	Background* background;
	list<Enemy*> enemies;
	list<Projectile*> projectiles;

	bool controlShoot = false;
	int controlMoveY = 0;
	int controlMoveX = 0;

	Actor* backgroundPoints;
	Text* textPoints;
	int points;



};


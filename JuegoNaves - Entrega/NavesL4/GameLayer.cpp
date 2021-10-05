#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	init();
}

void GameLayer::init() {

	audioBackground = new Audio("res/musica_ambiente.mp3", true);
	audioBackground->play();

	player = new Player(50, 50, game);
	background = new Background("res/fondo.png", WIDTH * 0.5, HEIGHT * 0.5, -1, game);

	enemies.clear(); // Vaciar por si reiniciamos el juego
	projectiles.clear(); // Vaciar por si reiniciamos el juego
	enemyProjectiles.clear();
	coins.clear();
	bombs.clear();

	backgroundPoints = new Actor("res/icono_puntos.png",
		WIDTH * 0.85, HEIGHT * 0.05, 24, 24, game);

	backgroundHealth = new Actor("res/corazon.png",
		WIDTH * 0.10, HEIGHT * 0.07, 44, 36, game);

	points = 0;
	textPoints = new Text("puntos", WIDTH * 0.92, HEIGHT * 0.05, game);
	textPoints->content = to_string(points);

	textHealth = new Text("vidas", WIDTH * 0.10, HEIGHT * 0.07, game);
	textHealth->content = to_string(player->lives);
}

void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		keysToControls(event);
	}
	//procesar controles
	//procesar controles
	// Disparar
	if (controlShoot) {
		Projectile* newProjectile = player->shoot();
		if (newProjectile != NULL) {
			projectiles.push_back(newProjectile);
		}

	}

	// Eje X
	if (controlMoveX > 0) {
		player->moveX(1);
	}
	else if (controlMoveX < 0) {
		player->moveX(-1);
	}
	else {
		player->moveX(0);
	}

	// Eje Y
	if (controlMoveY > 0) {
		player->moveY(1);
	}
	else if (controlMoveY < 0) {
		player->moveY(-1);
	}
	else {
		player->moveY(0);
	}
}

void GameLayer::update() {
	player->update();
	background->update();

	for (auto const& enemy : enemies) {
		enemy->update();
		EnemyProjectile* newProjectile = enemy->shoot();
		if (newProjectile != NULL) {
			enemyProjectiles.push_back(newProjectile);
		}
	}

	for (auto const& projectile : projectiles) {
		projectile->update();
	}

	for (auto const& enemyProjectile : enemyProjectiles) {
		enemyProjectile->update();
	}

	for (auto const& coin : coins) {
		coin->update();
	}
	
	for (auto const& bomb : bombs) {
		bomb->update();
	}
	// Generar enemigos
	newEnemyTime--;
	if (newEnemyTime <= 0) {
		int rX = (rand() % (600 - 500)) + 1 + 500;
		int rY = (rand() % (300 - 60)) + 1 + 60;
		enemies.push_back(new StandardEnemy(rX, rY, game));
		newEnemyTime = 150;
	}

	// Generar enemigos rojos
	newRedEnemyTime--;
	if (newRedEnemyTime <= 0) {
		int rX = (rand() % (600 - 500)) + 1 + 500;
		int rY = (rand() % (300 - 60)) + 1 + 60;
		enemies.push_back(new RedEnemy(rX, rY, game));
		newRedEnemyTime = 100;
	}

	// Generar monedas
	newCoinTime--;
	if (newCoinTime <= 0) {
		int rX = (rand() % (600 - 500)) + 1 + 500;
		int rY = (rand() % (300 - 60)) + 1 + 60;
		coins.push_back(new Coin(rX, rY, game));
		newCoinTime = 300;
	}


	// Generar monedas
	newBombTime--;
	if (newBombTime <= 0) {
		int rX = (rand() % (600 - 500)) + 1 + 500;
		int rY = (rand() % (300 - 60)) + 1 + 60;
		bombs.push_back(new Bomb(rX, rY, game));
		newBombTime = 500;
	}

	list<Enemy*> deleteEnemies;
	list<Projectile*> deleteProjectiles;
	list<EnemyProjectile*> deleteEnemyProjectiles;
	list<Coin*> deleteCoins;
	list<Bomb*> deleteBombs;

	// Colisiones
	for (auto const& enemy : enemies) {
		if (player->isOverlap(enemy)) {
		
			player->lives -= 1;
			textHealth->content = to_string(player->lives);

			if (player->lives <= 0) {
				init();
				return; // Cortar el fors
			}
			cout << player->lives;

			deleteEnemies.push_back(enemy);

		}
	}

	// Colisiones , Enemy - Projectile

	for (auto const& projectile : projectiles) {
		if (projectile->isInRender() == false) {

			bool pInList = std::find(deleteProjectiles.begin(),
				deleteProjectiles.end(),
				projectile) != deleteProjectiles.end();

			if (!pInList) {
				deleteProjectiles.push_back(projectile);
			}
		}
	}

	for (auto const& enemy : enemies) {
		for (auto const& projectile : projectiles) {
			if (enemy->isOverlap(projectile)) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}

				bool eInList = std::find(deleteEnemies.begin(),
					deleteEnemies.end(),
					enemy) != deleteEnemies.end();

				if (!eInList) {
					deleteEnemies.push_back(enemy);
				}
				points++;
				textPoints->content = to_string(points);

			}
		}
	}

	// Colisiones , Player - Projectile

	for (auto const& enemyProjectile : enemyProjectiles) {
		if (enemyProjectile->isInRender() == false) {

			bool pInList = std::find(deleteEnemyProjectiles.begin(),
				deleteEnemyProjectiles.end(),
				enemyProjectile) != deleteEnemyProjectiles.end();

			if (!pInList) {
				deleteEnemyProjectiles.push_back(enemyProjectile);
			}
		}
	}

	for (auto const& enemyProjectile : enemyProjectiles) {
		if (enemyProjectile->isOverlap(player)) {
			
			player->lives -= 1;
			textHealth->content = to_string(player->lives);
			
			cout << player->lives;
			
			if (player->lives <= 0) {
				init();
				return; // Cortar el fors
			}

			deleteEnemyProjectiles.push_back(enemyProjectile);

		}
	}

	// Colisiones , Player - Coin

	for (auto const& coin : coins) {
		if (player->isOverlap(coin)) {
			points += 10;
			textPoints->content = to_string(points);
			deleteCoins.push_back(coin);
		}
	}

	// Colisiones , Player - Bomb

	for (auto const& bomb : bombs) {
		if (player->isOverlap(bomb)) {
			
			bomb->explote(); //Efecto de sonido

			for (auto const& enemy : enemies) { //Elimina todos los enemigos
				points++;
				deleteEnemies.push_back(enemy);
			}

			textPoints->content = to_string(points);
			deleteBombs.push_back(bomb);
		}
	}

	// Limpiar enemigos y proyectiles.
	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
		delete delEnemy;
	}
	deleteEnemies.clear();

	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
		delete delProjectile;
	}
	deleteProjectiles.clear();

	for (auto const& delEProjectile : deleteEnemyProjectiles) {
		enemyProjectiles.remove(delEProjectile);
		delete delEProjectile;
	}
	deleteEnemyProjectiles.clear();

	// Limpiar monedas
	for (auto const& delCoin : deleteCoins) {
		coins.remove(delCoin);
		delete delCoin;
	}
	deleteCoins.clear();

	// Limpiar bombas
	for (auto const& delBomb : deleteBombs) {
		bombs.remove(delBomb);
		delete delBomb;
	}
	deleteBombs.clear();

	cout << "update GameLayer" << endl;
}

void GameLayer::draw() {
	background->draw();
	player->draw();

	for (auto const& projectile : projectiles) {
		projectile->draw();
	}

	for (auto const& enemyProjectile : enemyProjectiles) {
		enemyProjectile->draw();
	}

	for (auto const& enemy : enemies) {
		enemy->draw();
	}

	for (auto const& coin : coins) {
		coin->draw();
	}

	for (auto const& bomb : bombs) {
		bomb->draw();
	}

	textPoints->draw();
	backgroundPoints->draw();

	
	backgroundHealth->draw();
	textHealth->draw();

	SDL_RenderPresent(game->renderer); // Renderiza
}

void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_1:
			game->scale();
			break;
		case SDLK_d: // derecha
			controlMoveX = 1;
			break;
		case SDLK_a: // izquierda
			controlMoveX = -1;
			break;
		case SDLK_w: // arriba
			controlMoveY = -1;
			break;
		case SDLK_s: // abajo
			controlMoveY = 1;
			break;
		case SDLK_SPACE: // dispara
			controlShoot = true;
			break;
		}


	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY == -1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_SPACE: // dispara
			controlShoot = false;
			break;
		}

	}

}


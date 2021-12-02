#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	pause = true;
	message = new Actor("res/mensaje_como_jugar.png", WIDTH * 0.5, HEIGHT * 0.5,
		WIDTH, HEIGHT, game);

	//llama al constructor del padre : Layer(renderer)
	init();
}

void GameLayer::init() {
	space = new Space(0);

	audioBackground = new Audio("res/Sore_Point.mp3", true);
	audioBackground->play();

	background = new Background("res/fondo_3.png", WIDTH * 0.5, HEIGHT * 0.5, -1, game);

	// Vaciar por si reiniciamos el juego
	pathTiles.clear();
	buildableTiles.clear();
	enemies.clear(); 
	towerProjectiles.clear();
	towers.clear();

	selectedTile = NULL;
	selectedTower = NULL;

	lives = 20;
	points = 200;

	//Cargar HUD
	loadHUD();
	//Cargar mapa
	loadMap("res/map" + to_string(game->currentLevel) + ".txt");
	
	// Ordenar las pathTiles
	pathTiles = ordenaPathTiles();

}

list<PathTile*> GameLayer::ordenaPathTiles() {

	// Ordenar las pathTiles para el algoritmo de movimiento de los enenigos no es lo mas optimo pero bueno sirve.
	this->pathTiles.sort([](const PathTile* a, const PathTile* b) {
		if (a->x < b->x) {
			return 1;
		}
		return 0;
		});

	list<PathTile*> newPathTiles;
	list<PathTile*> auxPathTiles = pathTiles;
	PathTile* prevPathTile = pathTiles.front();
	newPathTiles.push_back(prevPathTile);
	auxPathTiles.remove(prevPathTile);

	while (newPathTiles.size() != pathTiles.size()) {
		for (auto const& pathTile : auxPathTiles) {

			if (abs(prevPathTile->x - pathTile->x) == 40 && abs(prevPathTile->y - pathTile->y) == 0) {
				prevPathTile = pathTile;
				newPathTiles.push_back(pathTile);
				auxPathTiles.remove(prevPathTile);
				break;
			}

			if (abs(prevPathTile->x - pathTile->x) == 0 && abs(prevPathTile->y - pathTile->y) == 40) {
				prevPathTile = pathTile;
				newPathTiles.push_back(pathTile);
				auxPathTiles.remove(prevPathTile);
				break;
			}
		}

	}

	return newPathTiles;

}

void GameLayer::loadHUD() {
	//Interfaz torres

	//buttonBasicTower
	buttonBasicTower = new Actor("res/button_basic_tower.png", WIDTH * 0.6, HEIGHT * 0.90, 50, 50, game);
	textPrecioBasic = new Text("precioBasic", WIDTH * 0.6, HEIGHT * 0.97, game);
	textPrecioBasic->content = to_string(precioBasic);
	//buttonCannonTower
	buttonCannonTower = new Actor("res/button_cannon_tower.png", WIDTH * 0.7, HEIGHT * 0.90, 50, 50, game);
	textPrecioCannon = new Text("precioCannon", WIDTH * 0.7, HEIGHT * 0.97, game);
	textPrecioCannon->content = to_string(precioCannon);
	//buttonFreezeTower
	buttonFreezeTower = new Actor("res/button_freeze_tower.png", WIDTH * 0.8, HEIGHT * 0.90, 50, 50, game);
	textPrecioFreeze = new Text("precioFreeze", WIDTH * 0.8, HEIGHT * 0.97, game);
	textPrecioFreeze->content = to_string(precioFreeze);
	//buttonBlastTower
	buttonBlastTower = new Actor("res/button_blast_tower.png", WIDTH * 0.9, HEIGHT * 0.90, 50, 50, game);
	textPrecioBlast = new Text("precioBlast", WIDTH * 0.9, HEIGHT * 0.97, game);
	textPrecioBlast->content = to_string(precioBlast);

	//Interfaz puntos
	backgroundPoints = new Actor("res/puntos.png",
		WIDTH * 0.85, HEIGHT * 0.05, 44, 36, game);

	textPoints = new Text("puntos", WIDTH * 0.90, HEIGHT * 0.05, game);
	textPoints->content = to_string(points);

	//Interfaz Vidas
	backgroundLives = new Actor("res/corazon.png",
		WIDTH * 0.70, HEIGHT * 0.06, 44, 36, game);

	textLives = new Text("vidas", WIDTH * 0.77, HEIGHT * 0.05, game);
	textLives->content = to_string(lives);
	
}

void GameLayer::update() {
	

	if (pause) {
		return;
	}

	space->update();
	
	background->update();

	//Generacion de enemigos
	if (timeToNewEnemy <= 0) {
		timeToNewEnemy = newEnemyTime;
		StandardEnemy* se = new  StandardEnemy(initialTile->x, initialTile->y, pathTiles, game);
		enemies.push_back(se);
		space->addDynamicActor(se);
	}
	else {
		timeToNewEnemy--;
	}

	for (auto const& enemy : enemies) {
		enemy->update();
	}

	for (auto const& tower : towers) {
		tower->update();

		for (auto const& enemy : enemies) {
			// Mirar si hay enemigos en el rango entonces disparar
			if (tower->hasInRange(enemy)) {
				TowerProjectile* newProjectile = tower->shoot(enemy);
				if (newProjectile != NULL) {
					space->addDynamicActor(newProjectile);
					towerProjectiles.push_back(newProjectile);
				}
			}
		}
	}

	list<Enemy*> deleteEnemies;
	list<TowerProjectile*> deleteProjectiles;

	// Los proyectiles siempre van hacia el enemigo al que se le asigno en su creacion.
	for (auto const& tProjectile : towerProjectiles) {
		if (!tProjectile->update()) {
			//si el update devuelve false significa que ya no hay enemigo al que targetear.
			deleteProjectiles.push_back(tProjectile);
		}	
	}

	// COLISIONES 
	// Colisiones , Enemy - Projectile
	for (auto const& enemy : enemies) {
		for (auto const& projectile : towerProjectiles) {
			if (enemy->isOverlap(projectile)) {
				
				projectile->hit(enemy);

				if (projectile->getTimeToExpire() <= 0) {
					bool pInList = std::find(deleteProjectiles.begin(),
						deleteProjectiles.end(),
						projectile) != deleteProjectiles.end();

					if (!pInList) {
						deleteProjectiles.push_back(projectile);
					}
				}

			
				if (enemy->getHealthPoints() <= 0) {
					enemy->impacted();
					bool eInList = std::find(deleteEnemies.begin(),
						deleteEnemies.end(),
						enemy) != deleteEnemies.end();

					if (!eInList) {
						deleteEnemies.push_back(enemy);
					}
					//Actualizar puntos
					points += enemy->getPoints();
					textPoints->content = to_string(points);
				}

			}
		}
	}

	// Colision enemy - endTile
	for (auto const& enemy : enemies) {
		if (enemy->isOverlap(endTile)) {
			
			lives--;
			textLives->content = to_string(lives);
			
			bool eInList = std::find(deleteEnemies.begin(),
				deleteEnemies.end(),
				enemy) != deleteEnemies.end();

			if (!eInList) {
				deleteEnemies.push_back(enemy);
			}

			if (lives <= 0) {
				init();
				return;
			}
	}
	}
	// Si el projectil se sale de pantalla borrar.
	for (auto const& projectile : towerProjectiles) {
		if (projectile->isInRender() == false || projectile->vx == 0) {

			bool pInList = std::find(deleteProjectiles.begin(),
				deleteProjectiles.end(),
				projectile) != deleteProjectiles.end();

			if (!pInList) {
				deleteProjectiles.push_back(projectile);
			}
		}
	}

	// Limpiar 
	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
		space->removeDynamicActor(delEnemy);
		delete delEnemy;
	}
	deleteEnemies.clear();

	for (auto const& delProjectile : deleteProjectiles) {
		towerProjectiles.remove(delProjectile);
		space->removeDynamicActor(delProjectile);
		delete delProjectile;
	}
	deleteProjectiles.clear();

	cout << "update GameLayer" << endl;
}

void GameLayer::draw() {
	background->draw();

	//Dibujar casillas
	initialTile->draw();
	endTile->draw();

	for (auto const& pathTile : pathTiles) {
		pathTile->draw();
	}

	for (auto const& buildableTile : buildableTiles) {
		buildableTile->draw();
	}

	//Dibujar torres
	for (auto const& tower : towers) {
		tower->draw();
	}

	//Dibujar enemigos
	for (auto const& enemy : enemies) {
		enemy->draw();
	}

	//Dibujar projectiles
	for (auto const& tProjectile : towerProjectiles) {
		tProjectile->draw();
	}

	// HUD
	//Dibujar marcadores de puntos y vidas
	textPoints->draw();
	backgroundPoints->draw();

	textLives->draw();
	backgroundLives->draw();
	//Dibujar botones torres
	if (game->input == game->inputMouse) {
		buttonBasicTower->draw();
		textPrecioBasic->draw();

		buttonCannonTower->draw();
		textPrecioCannon->draw();

		buttonFreezeTower->draw();
		textPrecioFreeze->draw();

		buttonBlastTower->draw();
		textPrecioBlast->draw();

		if (selectedTower != NULL) {
			Actor* rangeCircle = new Actor("res/range_circle.png",selectedTower->x,selectedTower->y,
				(selectedTower->getRange()-1) *80 + 40, (selectedTower->getRange() - 1) * 80 + 40,200,200,game);
			rangeCircle->draw();
		}
	}

	if (pause) {
		message->draw();
	}

	SDL_RenderPresent(game->renderer); // Renderiza
}

void GameLayer::loadMap(string name) {
	char character;
	string line;
	ifstream streamFile(name.c_str());
	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de mapa" << endl;
		return;
	}
	else {
		// Por línea

		for (int i = 0; getline(streamFile, line); i++) {
			istringstream streamLine(line);
			mapWidth = line.length() * 40; // Ancho del mapa en pixels
			mapHeight += 40; //Alto del mapa en pixels
			// Por carácter (en cada línea)
			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character; // Leer character 
				cout << character;
				float x = 40 / 2 + j * 40; // x central
				float y = 40 + i * 40; // y suelo
				loadMapObject(character, x, y);
			}

			cout << character << endl;
		}
	}
	streamFile.close();
}

void GameLayer::loadMapObject(char character, float x, float y)
{
	switch (character) {
	case '0': {
		initialTile = new InitialTile("res/initial_tile.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		initialTile->y = initialTile->y - initialTile->height / 2;
		break;
	}
	case '9': {
		endTile = new EndTile("res/end_tile.png",x, y, game);
		// modificación para empezar a contar desde el suelo.
		endTile->y = endTile->y - endTile->height / 2;
		break;
	}
	case '#': {
		PathTile* pathTile = new PathTile("res/path_tile.png",x, y, game);
		// modificación para empezar a contar desde el suelo.
		pathTile->y = pathTile->y - pathTile->height / 2;
		pathTiles.push_back(pathTile);
		break;
	}

	case '@': {
		BuildableTile* buildableTile = new BuildableTile("res/buildable_tile.png",x, y, game);
		// modificación para empezar a contar desde el suelo.
		buildableTile->y = buildableTile->y - buildableTile->height / 2;
		buildableTiles.push_back(buildableTile);
		//space->addStaticActor(buildableTile);
		break;
	}
	}
}

void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		// Cambio automático de input

		if (event.type == SDL_KEYDOWN) {
			game->input = game->inputKeyboard;
		}

		if (event.type == SDL_MOUSEBUTTONDOWN) {
			game->input = game->inputMouse;
		}

		if (game->input == game->inputKeyboard) {
			keysToControls(event);
		}

		if (game->input == game->inputMouse) {
			mouseToControls(event);
		}

	}
	//procesar controles
	if (controlContinue) {
		pause = false;
		controlContinue = false;
	}
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
		}
	}
}

void GameLayer::mouseToControls(SDL_Event event) {
	// Modificación de coordenadas por posible escalado
	float motionX = event.motion.x / game->scaleLower;
	float motionY = event.motion.y / game->scaleLower;
	// Cada vez que hacen click
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		controlContinue = true;
	
		//Mirar si selecciono una casilla construible
		for (auto const& buildableTile : buildableTiles) {
			if (buildableTile->containsPoint(motionX, motionY) && !buildableTile->isBuilt) {
				if (selectedTile != NULL) {
					selectedTile->texture = game->getTexture("res/buildable_tile.png");
				}
				// Que se deseleccione la torre si es que hubiera.
				selectedTower = NULL;

				selectedTile = buildableTile;
				buildableTile->texture = game->getTexture("res/buildable_tile_selected.png");
			}
		}

		//Interfaz torres
		if (buttonBasicTower->containsPoint(motionX, motionY)) {
			if (selectedTile != NULL && points >= precioBasic) {
				updatePoints(-precioBasic);
				towers.push_back(new BasicTower(selectedTile->x, selectedTile->y,game));
				//Marcar como construida y deseleccionar la casilla al acabar
				selectedTile->isBuilt = true;
				releaseTile();
			}

		}

		if (buttonCannonTower->containsPoint(motionX, motionY)) {
			if (selectedTile != NULL && points >= precioCannon) {
				updatePoints(-precioCannon);
				towers.push_back(new CannonTower(selectedTile->x, selectedTile->y, game));
				//Marcar como construida y deseleccionar la casilla al acabar
				selectedTile->isBuilt = true;
				releaseTile();
			}
		}

		if (buttonFreezeTower->containsPoint(motionX, motionY)) {
			if (selectedTile != NULL && points >= precioFreeze) {
				updatePoints(-precioFreeze);
				towers.push_back(new FreezeTower(selectedTile->x, selectedTile->y, game));
				//Marcar como construida y deseleccionar la casilla al acabar
				selectedTile->isBuilt = true;
				releaseTile();
			}
		}

		if (buttonBlastTower->containsPoint(motionX, motionY)) {
			if (selectedTile != NULL && points >= precioBlast) {
				updatePoints(-precioBlast);
				towers.push_back(new BlastTower(selectedTile->x, selectedTile->y, game));
				//Marcar como construida y deseleccionar la casilla al acabar
				selectedTile->isBuilt = true;
				releaseTile();
			}

		}

		for (auto const& tower : towers) {
			if (tower->containsPoint(motionX, motionY)) {
				selectedTower = tower;
				releaseTile();
		}
		}
		
	}
	// Cada vez que se mueve
	if (event.type == SDL_MOUSEMOTION) {
		

	}

	// Cada vez que levantan el click
	if (event.type == SDL_MOUSEBUTTONUP) {


	}

	
}

void GameLayer::releaseTile() {
	if (selectedTile != NULL) {
		selectedTile->texture = game->getTexture("res/buildable_tile.png");
		selectedTile = NULL;
	}
}
void GameLayer::updatePoints(int pointsToAdd) {
	points += pointsToAdd;
	textPoints->content = to_string(points);
}





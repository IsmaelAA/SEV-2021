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

	buttonJump = new Actor("res/boton_salto.png", WIDTH * 0.9, HEIGHT * 0.55, 100, 100, game);
	buttonShoot = new Actor("res/boton_disparo.png", WIDTH * 0.75, HEIGHT * 0.83, 100, 100, game);

	//buttonBasicTower
	//buttonCannonTower
	//buttonFreezeTower
	//buttonBlastTower

	pathTiles.clear();
	buildableTiles.clear();

	audioBackground = new Audio("res/Sore_Point.mp3", true);
	audioBackground->play();

	background = new Background("res/fondo_3.png", WIDTH * 0.5, HEIGHT * 0.5, -1, game);
	enemies.clear(); // Vaciar por si reiniciamos el juego
	projectiles.clear(); // Vaciar por si reiniciamos el juego
	eProjectiles.clear();
	

	//Interfaz puntos
	backgroundPoints = new Actor("res/puntos.png",
		WIDTH * 0.85, HEIGHT * 0.05, 44, 36, game);

	points = 0;

	textPoints = new Text("puntos", WIDTH * 0.92, HEIGHT * 0.05, game);
	textPoints->content = to_string(points);

	//Interfaz Vidas
	backgroundLives = new Actor("res/corazon.png",
		WIDTH * 0.70, HEIGHT * 0.06, 44, 36, game);

	lives = 10;

	textLives = new Text("vidas", WIDTH * 0.77, HEIGHT * 0.05, game);
	textLives->content = to_string(lives);

	//Cargar mapa
	loadMap("res/map" + to_string(game->currentLevel) + ".txt");

}

void GameLayer::update() {

	if (pause) {
		return;
	}

	
	space->update();
	
	background->update();

	for (auto const& enemy : enemies) {
		enemy->update();

		if (enemy->isInRender()) {
			EnemyProjectile* newProjectile = enemy->shoot();
			if (newProjectile != NULL) {
				space->addDynamicActor(newProjectile);
				eProjectiles.push_back(newProjectile);
			}
		}

	}

	for (auto const& projectile : projectiles) {
		projectile->update();
	}


	for (auto const& eProjectile : eProjectiles) {
		eProjectile->update();
	}


	list<Enemy*> deleteEnemies;
	list<Projectile*> deleteProjectiles;
	list<EnemyProjectile*> deleteEProjectiles;

	// Colisiones , Enemy - Projectile
	for (auto const& enemy : enemies) {
		for (auto const& projectile : projectiles) {
			if (enemy->isOverlap(projectile)) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}

				enemy->impacted();
				points++;
				textPoints->content = to_string(points);

			}
		}
	}


	for (auto const& projectile : projectiles) {
		if (projectile->isInRender() == false || projectile->vx == 0) {

			bool pInList = std::find(deleteProjectiles.begin(),
				deleteProjectiles.end(),
				projectile) != deleteProjectiles.end();

			if (!pInList) {
				deleteProjectiles.push_back(projectile);
			}
		}
	}

	for (auto const& projectile : eProjectiles) {
		if (projectile->isInRender() == false || projectile->vx == 0) {

			bool pInList = std::find(deleteEProjectiles.begin(),
				deleteEProjectiles.end(),
				projectile) != deleteEProjectiles.end();

			if (!pInList) {
				deleteEProjectiles.push_back(projectile);
			}
		}
	}

	for (auto const& enemy : enemies) {
		if (enemy->state == game->stateDead) {
			bool eInList = std::find(deleteEnemies.begin(),
				deleteEnemies.end(),
				enemy) != deleteEnemies.end();

			if (!eInList) {
				deleteEnemies.push_back(enemy);
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
		projectiles.remove(delProjectile);
		space->removeDynamicActor(delProjectile);
		delete delProjectile;
	}
	deleteProjectiles.clear();

	for (auto const& delEProjectile : deleteEProjectiles) {
		eProjectiles.remove(delEProjectile);
		space->removeDynamicActor(delEProjectile);
		delete delEProjectile;
	}
	deleteEProjectiles.clear();

	cout << "update GameLayer" << endl;
}

void GameLayer::draw() {
	background->draw();

	//Dibujar marcadores de puntos y vidas
	textPoints->draw();
	backgroundPoints->draw();

	textLives->draw();
	backgroundLives->draw();

	//Dibujar casillas
	initialTile->draw();
	endTile->draw();

	for (auto const& pathTile : pathTiles) {
		pathTile->draw();
	}

	for (auto const& buildableTile : buildableTiles) {
		buildableTile->draw();
	}

	// HUD
	if (game->input == game->inputMouse) {

		
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
	
		if (buttonShoot->containsPoint(motionX, motionY)) {
			controlShoot = true;
		}
		if (buttonJump->containsPoint(motionX, motionY)) {
			
		}

	}
	// Cada vez que se mueve
	if (event.type == SDL_MOUSEMOTION) {
		
		if (buttonShoot->containsPoint(motionX, motionY) == false) {
			controlShoot = false;
		}
		if (buttonJump->containsPoint(motionX, motionY) == false) {
			
		}

	}

	// Cada vez que levantan el click
	if (event.type == SDL_MOUSEBUTTONUP) {

		if (buttonShoot->containsPoint(motionX, motionY)) {
			controlShoot = false;
		}
		if (buttonJump->containsPoint(motionX, motionY)) {
			
		}

	}

	
}





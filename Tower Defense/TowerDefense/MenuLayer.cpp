#include "MenuLayer.h"

MenuLayer::MenuLayer(Game* game)
	: Layer(game) {
	init();
	
}

void MenuLayer::init() {
	// Fondo normal, sin velocidad
	background = new Background("res/menu_fondo.png", WIDTH * 0.5, HEIGHT * 0.5, game);
	buttonMap1 = new Actor("res/boton_jugar.png", WIDTH * 0.5, HEIGHT * 0.6, 232, 72, game);
	textMap1 = new Text("Nivel 1", WIDTH * 0.5, HEIGHT * 0.6, game);
	
	buttonMap2 = new Actor("res/boton_jugar.png", WIDTH * 0.5, HEIGHT * 0.7, 232, 72, game);
	textMap2 = new Text("Nivel 2", WIDTH * 0.5, HEIGHT * 0.7, game);
}

void MenuLayer::draw() {
	background->draw();
	buttonMap1->draw();
	buttonMap2->draw();
	textMap1->draw();
	textMap2->draw();

	SDL_RenderPresent(game->renderer); // Renderiza NO PUEDE FALTAR
}

void MenuLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		
		// Cambio automático de input
		// PONER el GamePad
		if (event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERAXISMOTION) {
			game->input = game->inputGamePad;
		}
		if (event.type == SDL_KEYDOWN) {
			game->input = game->inputKeyboard;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			game->input = game->inputMouse;
		}
		
		if (game->input == game->inputMouse) {
			mouseToControls(event);
		}
	}

	//procesar controles, solo tiene uno
	if (controlContinue) {
		// Cambia la capa
		game->gameLayer = new GameLayer(game);
		game->layer = game->gameLayer;
		controlContinue = false;
	}
}

void MenuLayer::mouseToControls(SDL_Event event) {
	// Modificación de coordenadas por posible escalado
	float motionX = event.motion.x / game->scaleLower;
	float motionY = event.motion.y / game->scaleLower;

	// Cada vez que hacen click
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (buttonMap1->containsPoint(motionX, motionY)) {
			game->currentLevel = 0;
			controlContinue = true;
		}
		if (buttonMap2->containsPoint(motionX, motionY)) {
			game->currentLevel = 1;
			controlContinue = true;
		}
	}
}

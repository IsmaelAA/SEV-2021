#pragma once

// Todas las librerias de SDL y otras utilidades
#include <iostream>
#include <string>
using namespace std;
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <map> 

// Valores generales
#define WIDTH 720
#define HEIGHT 480

#include "Layer.h"
class Layer;

class Game
{
public:
	Game();
	void scale();
	bool scaledToMax = false;
	float scaleLower = 1;
	void loop();
	SDL_Window* window; // ventana
	SDL_Renderer* renderer; // renderizador
	bool loopActive; // Juego activo
	Layer* layer;
	Layer* menuLayer;
	Layer* gameLayer;
	TTF_Font* font;

	SDL_Texture* getTexture(string filename);
	map<string, SDL_Texture*> mapTextures; // map - cache

	int const stateMoving = 1;
	int const stateJumping = 2;
	int const stateDying = 3;
	int const stateDead = 4;
	int const stateShooting = 5;

	int const orientationRight = 1;
	int const orientationLeft = 2;

	int currentLevel = 0;

	int input;
	int const inputKeyboard = 1;
	int const inputMouse = 2;
	int const inputGamePad = 3;



};

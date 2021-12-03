#pragma once

#include "Layer.h"
#include "GameLayer.h"
#include "Actor.h"
#include "Background.h"
#include "Text.h"

class MenuLayer : public Layer
{
public:
	MenuLayer(Game* game);
	void init() override;
	void draw() override;
	void processControls() override;
	
	void mouseToControls(SDL_Event event);
	bool controlContinue;

	Background* background;
	Actor* buttonMap1;
	Actor* buttonMap2;
	Text* textMap1;
	Text* textMap2;
};

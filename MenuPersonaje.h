
#pragma once

#include "Layer.h"
#include "Actor.h"
#include "Background.h"

class MenuPersonaje : public Layer
{
public:
	MenuPersonaje(Game* game);
	void init() override;
	void draw() override;
	void processControls() override;
	void keysToControls(SDL_Event event);
	void mouseToControls(SDL_Event event);
	void gamePadToControls(SDL_Event event);
	int controlJugadores = -1;
	int controlP1 = -1;
	int controlP2 = -1;
	SDL_GameController* gamePad; // Mando
	Background* background;
	Actor* button1;
	Actor* button2;
	Actor* per1;
	Actor* per2;
	Actor* per3;
	Actor* per4;
};

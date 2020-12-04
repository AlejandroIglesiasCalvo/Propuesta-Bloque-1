
#include "MenuLayer.h"

MenuLayer::MenuLayer(Game* game)
	: Layer(game) {
	init();
	gamePad = SDL_GameControllerOpen(0);
}

void MenuLayer::init() {
	// Fondo normal, sin velocidad
	background = new Background("res/capa2.png", WIDTH * 0.5, HEIGHT * 0.5, game);
	button1 = new Actor("res/1.png", WIDTH * 0.2, HEIGHT * 0.2, 25, 72, game);
	button2 = new Actor("res/2.png", WIDTH * 0.5, HEIGHT * 0.2, 25, 72, game);
	button3 = new Actor("res/3.png", WIDTH * 0.7, HEIGHT * 0.2, 25, 72, game);
}

void MenuLayer::draw() {
	background->draw();
	button1->draw();
	button2->draw();
	button3->draw();

	SDL_RenderPresent(game->renderer); // Renderiza NO PUEDE FALTAR
}
void MenuLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_CONTROLLERDEVICEADDED) {
			gamePad = SDL_GameControllerOpen(0);
			if (gamePad == NULL) {
				cout << "error en GamePad" << endl;
			}
			else {
				cout << "GamePad conectado" << endl;
			}
		}
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
		// Procesar teclas
		if (game->input == game->inputGamePad) {  // gamePAD
			gamePadToControls(event);
		}
		if (game->input == game->inputKeyboard) {
			keysToControls(event);
		}
		if (game->input == game->inputMouse) {
			mouseToControls(event);
		}
	}

	//procesar controles, solo tiene uno
	if (controlContinue<=-1) {
		// Cambia la capa
		game->mapa = controlContinue;
		game->layer = game->menuPersonaje;
	}
	
}
void MenuLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE: // derecha
			game->loopActive = false;
			break;
		case SDLK_1:
			game->scale();
			break;
		case SDLK_SPACE: // dispara
			controlContinue = true;
			break;
		}
	}
}
void MenuLayer::mouseToControls(SDL_Event event) {
	// Modificación de coordenadas por posible escalado
	float motionX = event.motion.x / game->scaleLower;
	float motionY = event.motion.y / game->scaleLower;

	// Cada vez que hacen click
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (button1->containsPoint(motionX, motionY)) {
			controlContinue = 1;
		}
		if (button2->containsPoint(motionX, motionY)) {
			controlContinue = 2;
		}
		if (button3->containsPoint(motionX, motionY)) {
			controlContinue = 3;
		}
	}
}
void MenuLayer::gamePadToControls(SDL_Event event) {
	// Leer los botones
	bool buttonA = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_A);

	if (buttonA) {
		controlContinue = true;
	}
}

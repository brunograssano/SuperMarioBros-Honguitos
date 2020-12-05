#include "GameLoop.hpp"


GameLoop::GameLoop(){
	salir = false;
}


bool GameLoop::inicializarAplicacion(info_partida_t informacion,Cliente* cliente){
	App* app = App::getInstance(informacion,cliente);
	return(app != nullptr);
};

void GameLoop::seMurioElServer(){
	salir = true;
};

void GameLoop::gameLoop() {
	App *aplicacion = App::getInstance();
	SDL_Event event;
	while (!salir) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				salir = true;
			}
		}
		SDL_PumpEvents();
		const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);
		if (keyboard_state_array[SDL_SCANCODE_ESCAPE]) {
			salir = true;
		} else {
			aplicacion->actualizarServer(keyboard_state_array);
		}
		aplicacion->actualizar();
		aplicacion->dibujar();
	}
	delete aplicacion;
};

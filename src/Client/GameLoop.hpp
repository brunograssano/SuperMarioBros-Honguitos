#ifndef SRC_CLIENT_GAMELOOP_HPP_
#define SRC_CLIENT_GAMELOOP_HPP_

#include <SDL2/SDL.h>

#include "../Utils/Utils.hpp"
#include "../Client/Cliente.hpp"
#include "app/AplicacionCliente.hpp"

void inicializarAplicacion(info_partida_t informacion,Cliente* cliente){
	App::getInstance(informacion,cliente);
}


void gameLoop() {
	App *aplicacion = App::getInstance();
	bool salir = false;
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
}



#endif /* SRC_CLIENT_GAMELOOP_HPP_ */

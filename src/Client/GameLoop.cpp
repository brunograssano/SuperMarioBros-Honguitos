#include "GameLoop.hpp"
#include "reproductorDeMusica/ReproductorMusica.hpp"
#include "src/Utils/Contador.hpp"
#include <SDL2/SDL.h>


GameLoop::GameLoop(){
	salir = false;
}


bool GameLoop::inicializarAplicacion(info_partida_t informacion,Cliente* cliente){
	App* app = App::getInstance(informacion,cliente);
	return(app != nullptr);
};

void GameLoop::seMurioElServer(){
	App* app = App::getInstance();
	if(app!=nullptr){
		app->ocurrioUnErrorServidor();
	}
};

void GameLoop::gameLoop() {
	App *aplicacion = App::getInstance();
	SDL_Event event;
	unsigned int microSegundosEspera = 11000;
	auto contador = Contador(microSegundosEspera, USEGUNDOS);
	while (!salir) {
		contador.iniciar();
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				salir = true;
			}
			else if (event.type == SDL_KEYDOWN){
			    aplicacion->manejarEntrada(event.key.keysym.sym);
			}else if(event.type == SDL_MOUSEBUTTONDOWN){
			    aplicacion->manejarClick(event);
			}
		}
		SDL_PumpEvents();
		const Uint8 *keyboard_state_array = SDL_GetKeyboardState(nullptr);
		if (keyboard_state_array[SDL_SCANCODE_ESCAPE]) {
			salir = true;
		} else {
			aplicacion->actualizarServer(keyboard_state_array);
		}
		aplicacion->actualizar();
		aplicacion->dibujar();
		usleep(contador.tiempoRestante());
	}
	delete aplicacion;
};

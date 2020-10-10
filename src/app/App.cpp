#include "App.h"



App* App::aplicacion = nullptr;

App* App::GetInstance(){// TODO Recibir la direccion del archivo a leer?
		if(aplicacion==nullptr){
			aplicacion = new App();
		}
		return aplicacion;
}


void App::actualizar(SDL_Event evento){




}

void App::dibujar(){




}

SDL_Renderer* App::obtenerRenderizador(){
	return renderizador;
}



App::~App(){
	SDL_DestroyRenderer( renderizador );
	SDL_DestroyWindow( ventanaAplicacion );

	IMG_Quit();
	SDL_Quit();

	delete cargadorTexturas;

	// TODO delete del juego
}




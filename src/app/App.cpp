#include "App.h"



App* App::aplicacion = nullptr;

App* App::GetInstance(){// TODO Recibir la direccion del archivo a leer?
		if(aplicacion==nullptr){
			aplicacion = new App();
		}
		return aplicacion;
}


void App::actualizar(SDL_Event evento){
	Mario* jugador = Juego::getInstance()->obtenerMario();
	switch(evento.key.keysym.sym){
		case SDLK_UP:
			jugador->moveraAbajo();
		break;
		case SDLK_DOWN:
			jugador->moveraArriba();
		break;

		case SDLK_LEFT:
			jugador->aceleraraIzquierda();
		break;

		case SDLK_RIGHT:
			jugador->aceleraraDerecha();
		break;

		default:
		break;
	}
	jugador->actualizarPosicion();



}

void App::dibujar(){

	Mario* mario = Juego::getInstance()->obtenerMario();
	SDL_Rect rectanguloMario = {mario->obtenerPosicionX(),mario->obtenerPosicionY(), 40, 80};

	//SDL_SetRenderDrawColor( renderizador, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( renderizador );


	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaMario(), NULL, &rectanguloMario);

	SDL_RenderPresent( renderizador );

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
	delete juego;
}




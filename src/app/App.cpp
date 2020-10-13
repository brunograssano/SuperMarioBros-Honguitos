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
			spriteMario->actualizarSpriteMarioSaltar(jugador, cargadorTexturas, renderizador);
		break;
		case SDLK_DOWN:
			spriteMario->actualizarSpriteMarioAgacharse(jugador, cargadorTexturas, renderizador);
		break;
		case SDLK_LEFT:
			spriteMario->actualizarSpriteMarioIzquierda(jugador, cargadorTexturas, renderizador);
		break;
		case SDLK_RIGHT:
			spriteMario->actualizarSpriteMarioDerecha(jugador, cargadorTexturas, renderizador);
		break;

		case SDLK_SPACE:
			spriteMario->actualizarSpriteMarioSaltar(jugador, cargadorTexturas, renderizador);
		break;
		default:
			spriteMario->actualizarSpriteMarioQuieto(jugador, cargadorTexturas, renderizador);
		break;
	}
}

void App::actualizar(){
	Mario* jugador = Juego::getInstance()->obtenerMario();
	jugador->actualizarPosicion();
	Juego::getInstance()->actualizarPosicionesEnemigos();
}

void App::dibujar(){

	Mario* mario = Juego::getInstance()->obtenerMario();
	SDL_Rect rectanguloMario = {mario->obtenerPosicionX(),420 - mario->obtenerPosicionY(), 40, 80};

	list<Enemigo*> enemigos = Juego::getInstance()->obtenerEnemigos();
	SDL_Rect rectanguloGoomba = {enemigos.front()->obtenerPosicionX(),enemigos.front()->obtenerPosicionY(), 40, 35};

	//SDL_SetRenderDrawColor( renderizador, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( renderizador );


	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaMario(), NULL, &rectanguloMario);
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaMoneda(), NULL, &rectanguloGoomba);
							// esta en el de la moneda para probar solamente

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
	delete spriteMario;
}




#include "App.h"
#include <list>

App* App::aplicacion = nullptr;
const int SE_TERMINO_EL_TIEMPO = 0;

App* App::getInstance(ArchivoLeido* archivoLeido){
	if(aplicacion==nullptr){
		aplicacion= new App(archivoLeido);
	}
	return aplicacion;
}

App* App::getInstance(){
		return aplicacion;
}


void App::actualizar(SDL_Event evento){
	Mario* jugador = Juego::getInstance()->obtenerMario();
	switch(evento.key.keysym.sym){
		case SDLK_UP:
		case SDLK_SPACE:
			spriteMario->actualizarSpriteMarioSaltar(jugador);
		break;
		case SDLK_DOWN:
			spriteMario->actualizarSpriteMarioAgacharse(jugador);
		break;
		case SDLK_LEFT:
			spriteMario->actualizarSpriteMarioIzquierda(jugador);
		break;
		case SDLK_RIGHT:
			spriteMario->actualizarSpriteMarioDerecha(jugador);
		break;
	}
}

void App::actualizar(){
	if(!terminoElJuego){
		Mario* jugador = Juego::getInstance()->obtenerMario();
		jugador->actualizarPosicion();
		Juego::getInstance()->actualizarPosicionesEnemigos();
		spriteMario->actualizarSprite(jugador);
		revisarSiTerminoNivel(jugador);
		cargadorTexturas->revisarSiCambioNivel(renderizador);
		moverCamara(jugador);
	}
}


void App::revisarSiTerminoNivel(Mario* jugador){

	if(jugador->obtenerPosicionX()>=ANCHO_FONDO-500){ //PONER EL FIN DEL NIVEL EN EL XML?
		rectanguloCamara.x= 0;
		rectanguloCamara.y = 0;
		juego->avanzarNivel();
		tiempoDeInicio = SDL_GetTicks();
	}


}

SDL_Rect* App::obtenerRectCamara(){
	return &rectanguloCamara;
}


void App::moverCamara(Mario* jugador){

	SDL_Rect* rectanguloCamara = obtenerRectCamara();

	bool elJugadorEstaIntentandoIrAlLadoDerechoDeLaPantalla = jugador->obtenerPosicionX() > rectanguloCamara->x + (ancho_pantalla)/2;

	if( elJugadorEstaIntentandoIrAlLadoDerechoDeLaPantalla ){
		rectanguloCamara->x =   jugador->obtenerPosicionX() - (ancho_pantalla) / 2 ;
		jugador->actualizarMaximoX(rectanguloCamara->x);
	}

	if( rectanguloCamara->x < 0 ){
		 rectanguloCamara->x = 0;
	}

	if( rectanguloCamara->x > ANCHO_FONDO - ancho_pantalla){
		rectanguloCamara->x = ANCHO_FONDO - ancho_pantalla;
	}
}

void App::dibujar(){
	tiempoFaltante = ((juego->obtenerTiempoDelNivel()*1000) - SDL_GetTicks() + tiempoDeInicio)/1000;
	//tiempoFaltante = ((20*1000) - SDL_GetTicks() + tiempoDeInicio)/1000; // PARA PROBAR LA PANTALLA DE GAME OVER
	if(tiempoFaltante<=SE_TERMINO_EL_TIEMPO){
		dibujador->dibujarGameOver();
		terminoElJuego = true;
	}else if(!terminoElJuego){
		dibujador->dibujar(&rectanguloCamara);
	}
}


int App::obtenerTiempoFaltante(){
	return tiempoFaltante;
}

SDL_Renderer* App::obtenerRenderizador(){
	return renderizador;
}

App::~App(){
	SDL_DestroyRenderer( renderizador );
	SDL_DestroyWindow( ventanaAplicacion );

	IMG_Quit();
	SDL_Quit();

	delete dibujador;
	delete cargadorTexturas;
	delete juego;
	delete spriteMario;
}

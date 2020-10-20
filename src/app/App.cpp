#include "App.h"

#include <list>

App* App::aplicacion = nullptr;

App* App::GetInstance(ArchivoLeido* archivoLeido){
	if(aplicacion==nullptr){
		aplicacion= new App(archivoLeido);
	}
	return aplicacion;
}

App* App::GetInstance(){
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
	Mario* jugador = Juego::getInstance()->obtenerMario();
	jugador->actualizarPosicion();
	Juego::getInstance()->actualizarPosicionesEnemigos();
	spriteMario->actualizarSprite(jugador);
	cargadorTexturas->revisarSiCambioNivel(renderizador);
	moverCamara();
}



SDL_Rect* App::obtenerRectCamara(){
	return &rectanguloCamara;
}



void App::moverCamara(){

	Mario* jugador = Juego::getInstance()->obtenerMario();
	SDL_Rect* rectanguloCamara = obtenerRectCamara();

	bool elJugadorEstaIntentandoIrAlLadoDerechoDeLaPantalla = jugador->obtenerPosicionX() > rectanguloCamara->x + (ancho_pantalla)/2;

	if( elJugadorEstaIntentandoIrAlLadoDerechoDeLaPantalla ){
		rectanguloCamara->x =   jugador->obtenerPosicionX() - (ancho_pantalla) / 2 ;
	}

	if( rectanguloCamara->x < 0 ){
		 rectanguloCamara->x = 0;
	}

	if( rectanguloCamara->x > ANCHO_FONDO - ancho_pantalla){
		rectanguloCamara->x = ANCHO_FONDO - ancho_pantalla;
	}
}




void App::dibujar(){

	SDL_Rect* rectanguloCamara = obtenerRectCamara();

	SDL_RenderClear( renderizador );

	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaFondo(), rectanguloCamara, NULL);

	Mario* mario = Juego::getInstance()->obtenerMario();
	SDL_Rect rectanguloMario = {mario->obtenerPosicionX() - rectanguloCamara->x,458 - mario->obtenerPosicionY(), 40, 80};
	int recorteX = spriteMario->obtenerPosicionXRectangulo();
	SDL_Rect recorteMario = {recorteX, 0, 16, 32};
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaMario(), &recorteMario, &rectanguloMario);

	list<Enemigo*> enemigos = Juego::getInstance()->obtenerEnemigos();
	for (auto const& enemigo : enemigos) {
	    //enemigo->actualizarPosicion();

		SDL_Rect rectanguloEnemigo;
		Sprite* spriteEnemigo = enemigo->obtenerSprite();
		rectanguloEnemigo = spriteEnemigo->obtenerRectanguloActual();
		rectanguloEnemigo.x+=enemigo->obtenerPosicionX() - rectanguloCamara->x;
		int valorX = spriteEnemigo->obtenerPosicionXRectangulo();
		SDL_Rect recorteTextura = {valorX,0, 16, 32};
	    SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaEnemigo(spriteEnemigo,renderizador), &recorteTextura, &rectanguloEnemigo);
	}

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




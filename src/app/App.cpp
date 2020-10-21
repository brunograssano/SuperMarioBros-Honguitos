#include "App.h"

#include <list>
#include <sstream>

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


void App::dibujarEnemigos(SDL_Rect* rectanguloCamara){
	list<Enemigo*> enemigos = Juego::getInstance()->obtenerEnemigos();
	for (auto const& enemigo : enemigos) {

		SDL_Rect recorteTextura;
		Sprite* spriteEnemigo = enemigo->obtenerSprite();
		recorteTextura = spriteEnemigo->obtenerRectanguloActual();

		SDL_Rect rectanguloEnemigo = {enemigo->obtenerPosicionX()-rectanguloCamara->x, 472 , 32, 64};

	    SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaEnemigo(spriteEnemigo,renderizador), &recorteTextura, &rectanguloEnemigo);
	}
}


void App::dibujarPlataformas(SDL_Rect* rectanguloCamara){
	list<Plataforma*> plataformas = Juego::getInstance()->obtenerPlataformas();

	for(auto const& plataforma : plataformas){
		list<Bloque*> bloques = plataforma->obtenerBloques();
		for (auto const& bloque : bloques) {

			SDL_Rect rectanguloBloque = {bloque->obtenerPosicionX() - rectanguloCamara->x,bloque->obtenerPosicionY(), 40, 40};
			Sprite* spriteBloque = bloque->obtenerSprite();
			SDL_Rect recorteBloque = spriteBloque->obtenerRectanguloActual();
			SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaBloque(spriteBloque, renderizador), &recorteBloque, &rectanguloBloque);
		}
	}
}


void App::dibujarMario(SDL_Rect* rectanguloCamara){
	Mario* mario = Juego::getInstance()->obtenerMario();
	SDL_Rect rectanguloMario = {mario->obtenerPosicionX() - rectanguloCamara->x,458 - mario->obtenerPosicionY(), 40, 80};
	int recorteX = spriteMario->obtenerPosicionXRectangulo();
	SDL_Rect recorteMario = {recorteX, 0, 16, 32};
	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaMario(), &recorteMario, &rectanguloMario);
}



void App::renderizarTexto(SDL_Rect renderQuad,string textoAMostrar ){
	SDL_Rect* clip = NULL;
	double angle = 0.0;
	SDL_Point* center = NULL;
	SDL_RendererFlip flip = SDL_FLIP_NONE;


	SDL_SetRenderDrawColor( renderizador, 0xFF, 0xFF, 0xFF, 0xFF );

	//Set clip rendering dimensions
	if( clip != NULL ){
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_Texture* texto = cargadorTexturas->cargarFuenteDeTextoATextura(textoAMostrar, renderizador);

	SDL_RenderCopyEx( renderizador, texto, clip, &renderQuad, angle, center, flip );
	SDL_DestroyTexture(texto);
}


void App::dibujarTexto(){
	//Set text to be rendered
	textoDeTiempo.str( "" );
	int tiempo = ((juego->obtenerTiempoDelNivel()*1000) - SDL_GetTicks() - tiempoDeInicio)/1000; //Getticks devuelve en milisegundos
	textoDeTiempo << "Tiempo restante " << tiempo;

	textoDeNivel.str("");
	textoDeNivel << "Mundo " << juego->obtenerMundoActual();

	textoDePuntos.str("");
	textoDePuntos << "Puntos " << juego->obtenerPuntuacionJugador();
	SDL_SetRenderDrawColor( renderizador, 0xFF, 0xFF, 0xFF, 0xFF );

	SDL_Rect cuadradoTiempo = { 450, 10, 330, 30 };
	SDL_Rect cuadradoMundo = { 200, 10, 100, 30 };
	SDL_Rect cuadradoPuntos = { 10, 10, 100, 30 };

	renderizarTexto(cuadradoTiempo, textoDeTiempo.str().c_str());
	renderizarTexto(cuadradoMundo, textoDeNivel.str().c_str());
	renderizarTexto(cuadradoPuntos, textoDePuntos.str().c_str());
}



void App::dibujar(){

	SDL_Rect* rectanguloCamara = obtenerRectCamara();

	SDL_RenderClear( renderizador );

	SDL_RenderCopy( renderizador, cargadorTexturas->obtenerTexturaFondo(), rectanguloCamara, NULL);

	dibujarMario(rectanguloCamara);

	dibujarEnemigos(rectanguloCamara);

	dibujarPlataformas(rectanguloCamara);

	dibujarTexto();

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




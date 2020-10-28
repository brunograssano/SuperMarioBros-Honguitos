#include "App.h"
#include <list>

App* App::aplicacion = nullptr;
const int SE_TERMINO_EL_TIEMPO = 0;
const int ALTO_VENTANA_MINIMO = 600,ANCHO_VENTANA_MINIMO = 800;


App* App::getInstance(ArchivoLeido* archivoLeido){
	if(aplicacion==nullptr){
		aplicacion= new App(archivoLeido);
	}
	return aplicacion;
}

App* App::getInstance(){
		return aplicacion;
}

void App::inicializarSDL(Log* log){
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		log->huboUnErrorSDL("Error inicializando SDL", SDL_GetError());
	}

	ventanaAplicacion = SDL_CreateWindow( "Super Mario Bros", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ancho_pantalla, alto_pantalla, SDL_WINDOW_SHOWN );
	if( ventanaAplicacion == NULL ){
		log->huboUnErrorSDL("No se pudo crear una ventana de SDL", SDL_GetError());
	}

	if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) ){
		log->huboUnErrorSDL("No se pudo inicializar IMG Init", IMG_GetError());
	}

	renderizador = SDL_CreateRenderer( ventanaAplicacion, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if( renderizador == NULL ){
		log->huboUnErrorSDL("No se pudo crear un renderizador de SDL", SDL_GetError());
	}

	string direccion = "resources/IconoHongo.png";
	SDL_Surface* icono = IMG_Load(direccion.c_str());
	if(icono == NULL){
		log->huboUnErrorSDL("No se pudo cargar el icono en: " + direccion, IMG_GetError());
	}
	else{
		SDL_SetWindowIcon(ventanaAplicacion, icono);
		SDL_FreeSurface(icono);
	}
}

void App::determinarDimensionesPantalla(int posibleAnchoVentana,int posibleAltoVentana){
	if(posibleAnchoVentana<ANCHO_VENTANA_MINIMO){
		posibleAnchoVentana = ANCHO_VENTANA_MINIMO;
	}
	if(posibleAltoVentana<ALTO_VENTANA_MINIMO){
		posibleAltoVentana = ALTO_VENTANA_MINIMO;
	}
	ancho_pantalla = posibleAnchoVentana;
	alto_pantalla = posibleAltoVentana;
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
	}else{
	}
}


void App::revisarSiTerminoNivel(Mario* jugador){

	if(jugador->obtenerPosicionX()>=juego->obtenerPuntoBanderaFinActual() && juego->quedaSoloUnNivel()){
		juego->sumarPuntosAJugadores(tiempoFaltante);
		ganaron = true;
		Log::getInstance()->mostrarMensajeDeInfo("Se terminaron los niveles del juego");
	}
	else if(jugador->obtenerPosicionX()>=juego->obtenerPuntoBanderaFinActual()){ //PONER EL FIN DEL NIVEL EN EL XML? si
		rectanguloCamara.x= 0;
		rectanguloCamara.y = 0;
		juego->avanzarNivel();
		juego->sumarPuntosAJugadores(tiempoFaltante);
		tiempoDeInicio = SDL_GetTicks();
		Log::getInstance()->mostrarMensajeDeInfo("Se avanzo de nivel");
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
	if(ganaron){
		dibujador->dibujarPantallaGanadores();
		terminoElJuego = true;
	}
	else if(tiempoFaltante<=SE_TERMINO_EL_TIEMPO || terminoElJuego){
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

void App::escribirMensajesDeArchivoLeidoEnLog(list<string> mensajesError){
	Log* log = Log::getInstance();
	for(auto const& mensaje:mensajesError){
		log->huboUnError(mensaje);
	}
}

App::~App(){

	Log::getInstance()->mostrarMensajeDeInfo("Se cierra la aplicacion");

	SDL_DestroyRenderer( renderizador );
	SDL_DestroyWindow( ventanaAplicacion );

	IMG_Quit();
	SDL_Quit();

	delete dibujador;
	delete cargadorTexturas;
	delete juego;
	delete spriteMario;
	delete Log::getInstance();
}

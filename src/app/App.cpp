#include "App.hpp"

#include <list>

App* App::aplicacion = nullptr;
const int SE_TERMINO_EL_TIEMPO = 0;
const int ALTO_VENTANA_MINIMO = 600,ANCHO_VENTANA_MINIMO = 800;

typedef struct entrada_usuario{
	bool A;
	bool S;
	bool D;
	bool W;
}entrada_usuario_t;

App* App::getInstance(info_partida_t informacion,TipoLog* tipoLog){
	if(aplicacion==nullptr){
		aplicacion= new App(informacion,tipoLog);
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

	string direccion = "resources/Imagenes/Personajes/IconoHongo.png";
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

void App::actualizarServer(const Uint8 *keystate){

	if(!juegoInicializadoCorrectamente){
		return;
	}

	if(!sePusoMusicaInicio){
		ReproductorMusica::getInstance()->ReproducirMusicaNivel("resources/Musica/MusicaInicio.mp3"); //TODO: refactorizar a otro método.
		sePusoMusicaInicio = true;
	}

	if(!comenzoElJuego){
		if(keystate[SDL_SCANCODE_RETURN]){
			comenzoElJuego = true;
			//tiempoDeInicio = SDL_GetTicks();
			ReproductorMusica::getInstance()->ReproducirMusicaNivel("resources/Musica/TemaNivel1.mp3"); //TODO: refactorizar a otro método.
		}
	}
	else if(!terminoElJuego){
		entrada_usuario_t entradaUsuario = {false,false,false,false};
		bool se_movio = false;
		//Mario* jugador = Juego::getInstance()->obtenerMario();
		if(keystate[SDL_SCANCODE_SPACE] || keystate[SDL_SCANCODE_UP]){
			//jugador->actualizarSaltarMario();
			entradaUsuario.W = true;
			se_movio = true;
		}

		if(keystate[SDL_SCANCODE_LEFT]){
			//jugador->actualizarIzquierdaMario();
			entradaUsuario.A = true;
			se_movio = true;
		}

		if(keystate[SDL_SCANCODE_RIGHT]){
			//jugador->actualizarDerechaMario();
			entradaUsuario.D = true;
			se_movio = true;
		}

		if(keystate[SDL_SCANCODE_DOWN] && !se_movio){
			entradaUsuario.S = true;
			//jugador->actualizarAgacharseMario();
		}
		//enviar entradaUsuario a el thread que lo envia

	}
}
/*
void App::actualizar(){
	if(!juegoInicializadoCorrectamente){
			return;
	}
	if(!terminoElJuego && comenzoElJuego){
		Mario* jugador = Juego::getInstance()->obtenerMario();
		jugador->actualizarPosicion();
		Juego::getInstance()->actualizarPosicionesEnemigos();
		revisarSiTerminoNivel(jugador);
		cargadorTexturas->revisarSiCambioNivel(renderizador);
		moverCamara(jugador);
	}
}
*/
/*
void App::revisarSiTerminoNivel(Mario* jugador){

	if(jugador->obtenerPosicionX()>=juego->obtenerPuntoBanderaFinActual() && juego->quedaSoloUnNivel()){
		juego->sumarPuntosAJugadores(tiempoFaltante);
		ganaron = true;
		Log::getInstance()->mostrarMensajeDeInfo("Se terminaron los niveles del juego");
		ReproductorMusica::getInstance()->ReproducirSonidoMarioAgarraHongo();
		ReproductorMusica::getInstance()->ReproducirMusicaNivel("resources/Musica/MusicaVictoria.mp3"); //TODO: refactorizar a otro método.
	}
	else if(jugador->obtenerPosicionX()>=juego->obtenerPuntoBanderaFinActual()){
		rectanguloCamara.x= 0;
		rectanguloCamara.y = 0;
		juego->avanzarNivel();
		juego->sumarPuntosAJugadores(tiempoFaltante);
		tiempoDeInicio = SDL_GetTicks();
		Log::getInstance()->mostrarMensajeDeInfo("Se avanzo de nivel");
	}


}
*/
/*
SDL_Rect* App::obtenerRectCamara(){
	return &rectanguloCamara;
}
*/
/*
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
*/

void App::dibujar(){

	if(!comenzoElJuego){
		dibujador->dibujarInicio();
	}
	else{
		if(ganaron){
			dibujador->dibujarPantallaGanadores();
			terminoElJuego = true;
		}
		else if(terminoElJuego){
			if(!terminoElJuego){
				ReproductorMusica::getInstance()->ReproducirMusicaNivel("resources/Musica/CoffinDance8Bits.mp3");
				terminoElJuego = true;
			}
			dibujador->dibujarGameOver();
		}else if(!terminoElJuego){
			dibujador->dibujarJuego(&rectanguloCamara,juegoCliente);
		}
	}
}

/*
int App::obtenerTiempoFaltante(){
	return tiempoFaltante;
}*/
/*
SDL_Renderer* App::obtenerRenderizador(){
	return renderizador;
}*/
/*
void App::escribirMensajesDeArchivoLeidoEnLog(list<string> mensajesError){
	Log* log = Log::getInstance();
	for(auto const& mensaje:mensajesError){
		log->huboUnError(mensaje);
	}
}
*/
App::~App(){

	Log::getInstance()->mostrarMensajeDeInfo("Se cierra la aplicacion");

	SDL_DestroyRenderer( renderizador );
	SDL_DestroyWindow( ventanaAplicacion );

	IMG_Quit();
	SDL_Quit();

	delete dibujador;
	delete cargadorTexturas;
	//delete juego;
	delete Log::getInstance();
	delete ReproductorMusica::getInstance();
}

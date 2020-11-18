#include "AplicacionServidor.hpp"

const int ANCHO_FONDO = 8177;


AplicacionServidor::AplicacionServidor(list<Nivel*> niveles,int cantidadJugadores,int ancho_pantalla ,int  alto_pantalla){
	juego = Juego::getInstance(niveles,cantidadJugadores);
	cantJugadores = cantidadJugadores;
	terminoElJuego = false;
	comenzoElJuego = false;
	ganaron = false;
	juegoInicializadoCorrectamente = false;
	log = Log::getInstance();
	tiempoDeInicio = 0;
	tiempoFaltante = 0;
	this->ancho_pantalla = ancho_pantalla;
	rectanguloCamara = { 0, 0, ancho_pantalla , alto_pantalla};
}


void AplicacionServidor::iniciarJuego(){
	comenzoElJuego = true;
}

void AplicacionServidor::gameLoop(){ //funcion que pasamos al hilo
	while(!comenzoElJuego){
		//estamos esperando a que nos indiquen que puede comenzar el juego
	}

	list<Mario*> jugadores = juego->obtenerMarios();
	while(!terminoElJuego){
		// revisar si tenemos comandos en la cola

		for(auto const& jugador:jugadores){
			jugador->actualizarPosicion();
		}
		juego->actualizarPosicionesEnemigos();
		revisarSiTerminoNivel(jugadores);
		moverCamara(jugadores);

		//transmitir a los clientes
		//esperar x tiempo?

	}


}

void AplicacionServidor::revisarSiTerminoNivel(list<Mario*> jugadores){

	bool pasadoLimite = true;
	int puntoBandera = juego->obtenerPuntoBanderaFinActual();
	for(auto const& jugador:jugadores){
		if(jugador->obtenerPosicionX()<puntoBandera){
			pasadoLimite = false;
		}
	}

	if(pasadoLimite && juego->quedaSoloUnNivel()){
		juego->sumarPuntosAJugadores(tiempoFaltante);
		ganaron = true;
		log->mostrarMensajeDeInfo("Se terminaron los niveles del juego");
	}
	else if(pasadoLimite){
		rectanguloCamara.x= 0;
		rectanguloCamara.y = 0;
		juego->avanzarNivel();
		juego->sumarPuntosAJugadores(tiempoFaltante);
		tiempoDeInicio = SDL_GetTicks();
		log->mostrarMensajeDeInfo("Se avanzo de nivel");
	}

}


SDL_Rect* AplicacionServidor::obtenerRectCamara(){
	return &rectanguloCamara;
}


void AplicacionServidor::moverCamara(list<Mario*> jugadores){
	SDL_Rect* rectanguloCamara = obtenerRectCamara();

	int posicionDelJugadorMasALaDerecha = 0;
	bool sePuedeMoverLaCamara = true;

	for(auto const& jugador: jugadores){
		if(jugador->obtenerPosicionX() <= rectanguloCamara->x){
			sePuedeMoverLaCamara = false;
		}
		if(jugador->obtenerPosicionX() > posicionDelJugadorMasALaDerecha){
			posicionDelJugadorMasALaDerecha = jugador->obtenerPosicionX();
		}

	}

	bool unJugadorEstaIntentandoIrAlLadoDerechoDeLaPantalla = posicionDelJugadorMasALaDerecha > rectanguloCamara->x + (ancho_pantalla)/2;

	if(sePuedeMoverLaCamara && unJugadorEstaIntentandoIrAlLadoDerechoDeLaPantalla){
		rectanguloCamara->x = posicionDelJugadorMasALaDerecha - (ancho_pantalla) / 2 ;

		for(auto const& jugador: jugadores){
			jugador->actualizarMaximoX(rectanguloCamara->x);
		}
	}

	/*if( rectanguloCamara->x < 0 ){
		 rectanguloCamara->x = 0;
	} No estoy seguro pero creo que ya no era neceserio*/

	if( rectanguloCamara->x > ANCHO_FONDO - ancho_pantalla){
		rectanguloCamara->x = ANCHO_FONDO - ancho_pantalla;
	}
}

AplicacionServidor::~AplicacionServidor(){

}



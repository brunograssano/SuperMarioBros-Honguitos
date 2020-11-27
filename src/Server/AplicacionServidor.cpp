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

info_partida_t AplicacionServidor::obtenerInfoPartida(map<int,string> mapaIDNombre,int IDJugador){
	Log::getInstance()->mostrarMensajeDeInfo("Se prepara la informacion de la partida para el jugador: " + mapaIDNombre[IDJugador]);
	info_partida_t info_partida;
	info_partida.altoVentana = rectanguloCamara.h;
	info_partida.anchoVentana = rectanguloCamara.w;
	info_partida.cantidadJugadores = cantJugadores;
	info_partida.idPropio = IDJugador;

	map<int,Mario*> jugadores = juego->obtenerMarios();

	for(int i=0;i<cantJugadores;i++){
		info_partida.jugadores[i].puntos = 0;
		info_partida.jugadores[i].mario.idImagen = i;
		info_partida.jugadores[i].mario.posX = jugadores[i]->obtenerPosicionX();
		info_partida.jugadores[i].mario.posY = jugadores[i]->obtenerPosicionY();
		info_partida.jugadores[i].mario.recorteImagen = jugadores[i]->obtenerSpite()->obtenerEstadoActual();
		strcpy(info_partida.jugadores[i].nombreJugador,mapaIDNombre[i].c_str());
	}

	list<Nivel*> niveles = juego->obtenerNiveles();
	int i = 0;
	for(auto& nivel:niveles){
		strcpy(info_partida.direccionesFondoNiveles[i],nivel->obtenerDireccionFondoActual().c_str());
		i++;
	}
	info_partida.cantidadFondosNiveles = i;
	return info_partida;

}


void AplicacionServidor::iniciarJuego(){
	comenzoElJuego = true;
}

void AplicacionServidor::actualizarPosicionDeJugador(Mario* jugador,entrada_usuario_t entrada){
	bool seMovio = false;
	if(entrada.A){
		jugador->actualizarIzquierdaMario();
		seMovio = true;
	}
	if(entrada.D){
		jugador->actualizarDerechaMario();
		seMovio = true;
	}
	if(entrada.W){
		jugador->actualizarSaltarMario();
		seMovio = true;
	}
	if(entrada.S && !seMovio){
		jugador->actualizarAgacharseMario();
	}
}


void AplicacionServidor::gameLoop(){ //funcion que pasamos al hilo
	while(!comenzoElJuego){
		//estamos esperando a que nos indiquen que puede comenzar el juego
	}
	Log::getInstance()->mostrarMensajeDeInfo("Inicia el ciclo del juego en el server");

	map<int,Mario*> jugadores = juego->obtenerMarios();
	while(!terminoElJuego){
		// revisar si tenemos comandos en la cola
		while(!colaDeEntradasUsuario.empty()){
			entrada_usuario_id_t parIDEntrada = colaDeEntradasUsuario.front();
			actualizarPosicionDeJugador(jugadores.at(parIDEntrada.id),parIDEntrada.entradas);
			colaDeEntradasUsuario.pop();
		}

		for(auto const& parClaveJugador:jugadores){
			parClaveJugador.second->actualizarPosicion();
		}
		juego->actualizarPosicionesEnemigos();
		revisarSiTerminoNivel(jugadores);
		moverCamara(jugadores);

		//transmitir a los clientes
		//esperar x tiempo?

	}

	Log::getInstance()->mostrarMensajeDeInfo("Termina el ciclo del juego en el server");
}

void AplicacionServidor::encolarEntradaUsuario(entrada_usuario_id_t entradaUsuario){
	this->colaDeEntradasUsuario.push(entradaUsuario);
}

void AplicacionServidor::revisarSiTerminoNivel(map<int,Mario*> jugadores){

	bool pasadoLimite = true;
	int puntoBandera = juego->obtenerPuntoBanderaFinActual();
	for(auto const& parClaveJugador:jugadores){
		if(parClaveJugador.second->obtenerPosicionX()<puntoBandera){
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


void AplicacionServidor::moverCamara(map<int,Mario*> jugadores){
	SDL_Rect* rectanguloCamara = obtenerRectCamara();

	int posicionDelJugadorMasALaDerecha = 0;
	bool sePuedeMoverLaCamara = true;
	Mario* jugador;

	for(auto const& parClaveJugador: jugadores){
		jugador = parClaveJugador.second;
		if(jugador->estaConectado() && (jugador->obtenerPosicionX() <= rectanguloCamara->x)){
			sePuedeMoverLaCamara = false;
		}
		if(jugador->obtenerPosicionX() > posicionDelJugadorMasALaDerecha){
			posicionDelJugadorMasALaDerecha = jugador->obtenerPosicionX();
		}

	}

	bool unJugadorEstaIntentandoIrAlLadoDerechoDeLaPantalla = posicionDelJugadorMasALaDerecha > rectanguloCamara->x + (ancho_pantalla)/2;

	if(sePuedeMoverLaCamara && unJugadorEstaIntentandoIrAlLadoDerechoDeLaPantalla){
		rectanguloCamara->x = posicionDelJugadorMasALaDerecha - (ancho_pantalla) / 2 ;

		for(auto const& parClaveJugador: jugadores){
			jugador = parClaveJugador.second;
			if((!jugador->estaConectado()) && (jugador->obtenerPosicionX()<rectanguloCamara->x)){
				jugador->serArrastrado(rectanguloCamara->x-jugador->obtenerPosicionX());
			}

			jugador->actualizarMaximoX(rectanguloCamara->x);
		}
	}

	if( rectanguloCamara->x < 0 ){
		 rectanguloCamara->x = 0;
	}

	if( rectanguloCamara->x > ANCHO_FONDO - ancho_pantalla){
		rectanguloCamara->x = ANCHO_FONDO - ancho_pantalla;
	}
}

AplicacionServidor::~AplicacionServidor(){

}



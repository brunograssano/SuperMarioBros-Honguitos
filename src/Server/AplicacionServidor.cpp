#include "AplicacionServidor.hpp"

#include <unistd.h>

#include <utility>

const int ANCHO_FONDO = 8177;

/*
 * Es el ancho que se permite hacia adelante y hacia atrás de la pantalla
 * para considerar a una entidad que está en el rango de visión
 */
const int ANCHO_RANGO = 100;

AplicacionServidor::AplicacionServidor(Servidor* server,list<Nivel*> niveles,int cantidadJugadores,int ancho_pantalla ,int  alto_pantalla){
	juego = Juego::getInstance(std::move(niveles),cantidadJugadores);
	cantJugadores = cantidadJugadores;
	terminoElJuego = false;
	comenzoElJuego = false;
	juegoInicializadoCorrectamente = false;
	log = Log::getInstance();
	servidor = server;
	this->ancho_pantalla = ancho_pantalla;
	rectanguloCamara = { 0, 0, ancho_pantalla , alto_pantalla};
}

info_partida_t AplicacionServidor::obtenerInfoPartida(map<int,string> mapaIDNombre,int IDJugador){
	Log::getInstance()->mostrarMensajeDeInfo("Se prepara la informacion de la partida para el jugador: " + mapaIDNombre[IDJugador]);
	info_partida_t info_partida;
	memset(&info_partida,0,sizeof(info_partida_t));

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
		strcpy(info_partida.direccionesFondoNiveles[i], nivel->obtenerDireccionFondoActual().c_str());
		i++;
	}
	info_partida.cantidadFondosNiveles = i;

	info_partida.mundo = juego->obtenerMundoActual();

	return info_partida;

}


bool AplicacionServidor::estaEnRangoVisible(int posicionX) const{

	return (posicionX + ANCHO_RANGO > rectanguloCamara.x) &&
		   (posicionX < rectanguloCamara.x + rectanguloCamara.w + ANCHO_RANGO);

}


info_ronda_t AplicacionServidor::obtenerInfoRonda(map<int,string> mapaIDNombre){

	Log::getInstance()->mostrarAccion("Se prepara la informacion de la ronda para enviar.");

	info_ronda_t info_ronda;
	memset(&info_ronda,0,sizeof(info_ronda_t));

	info_ronda.mundo = juego->obtenerMundoActual();
	info_ronda.posXCamara = this->rectanguloCamara.x;
	info_ronda.tiempoFaltante = this->juego->obtenerTiempoRestante();
	info_ronda.ganaron = juego->ganaron();
	info_ronda.perdieron = terminoElJuego && !juego->ganaron();

	list<Plataforma*> plataformas = juego->obtenerPlataformas();
	int numeroBloque = 0;
	for(auto const& plataforma: plataformas){
		list<bloque_t> bloques = plataforma->serializarPlataforma();

		for(auto const& bloque: bloques){
			if(estaEnRangoVisible(bloque.posX) &&
			numeroBloque<MAX_BLOQUES){
				info_ronda.bloques[numeroBloque] = bloque;
				numeroBloque++;
			}
		}
	}
	info_ronda.topeBloques = numeroBloque;

	int numeroEnemigo = 0;
	list<Enemigo*> enemigos = juego->obtenerEnemigos();
	for(auto const& enemigo: enemigos){
		if(estaEnRangoVisible(enemigo->obtenerPosicionX()) &&
		numeroEnemigo<MAX_ENEMIGOS){
			info_ronda.enemigos[numeroEnemigo] = enemigo->serializar();
			numeroEnemigo++;
		}
	}
	info_ronda.topeEnemigos = numeroEnemigo;

	int numeroMoneda = 0;
	list<Moneda*> monedas = juego->obtenerMonedas();
	for(auto const& moneda: monedas){
		if(estaEnRangoVisible(moneda->obtenerPosicionX()) &&
		numeroMoneda<MAX_MONEDAS){
			info_ronda.monedas[numeroMoneda] = moneda->serializar();
			numeroMoneda++;
		}
	}
	info_ronda.topeMonedas = numeroMoneda;

	map<int,Mario*> jugadores = juego->obtenerMarios();
	jugador_t jugadorSerializado;
	for(int i=0; i<cantJugadores; i++){
		jugadorSerializado = jugadores[i]->serializar(mapaIDNombre[i].c_str(), i);
		info_ronda.jugadores[i] = jugadorSerializado;
	}

	list<Tuberia*> tuberias = juego->obtenerTuberias();
	int numeroTuberia = 0;
    for(auto const& tuberia: tuberias){
        if(estaEnRangoVisible(tuberia->obtenerPosicionX()) &&
            numeroTuberia<MAX_TUBERIAS){
            info_ronda.tuberias[numeroTuberia] = tuberia->serializar();
            numeroTuberia++;
        }
    }
    info_ronda.topeTuberias = numeroTuberia;

	return info_ronda;
}

void AplicacionServidor::iniciarJuego(){
	comenzoElJuego = true;
}

void AplicacionServidor::gameLoop(){
	int microSegundosEspera = 16666;
	while(!comenzoElJuego){
	}

	Log::getInstance()->mostrarMensajeDeInfo("Inicia el ciclo del juego en el server");
	auto* contador = new Contador(microSegundosEspera, USEGUNDOS);
	map<int,Mario*> jugadores = juego->obtenerMarios();
    juego->iniciar();
	while(!terminoElJuego || tengoJugadores(jugadores)){
	    contador->iniciar();
		if(!terminoElJuego){

			while(!colaDeEntradasUsuario.empty()){
				entrada_usuario_id_t parIDEntrada = colaDeEntradasUsuario.front();
				juego->actualizarJugador(parIDEntrada.id, parIDEntrada.entradas);
				colaDeEntradasUsuario.pop();
			}
			juego->actualizarModelo(&rectanguloCamara);

			moverCamara(jugadores);

			terminoElJuego = juego->ganaron() || juego->perdieron();
		}
		info_ronda_t ronda = obtenerInfoRonda(servidor->obtenerMapaJugadores());
		servidor->guardarRondaParaEnvio(ronda);

		usleep(contador->tiempoRestante());
	}
	delete contador;
	Log::getInstance()->mostrarMensajeDeInfo("Termina el ciclo del juego en el server");
	servidor->terminoElJuego();
}

void AplicacionServidor::encolarEntradaUsuario(entrada_usuario_id_t entradaUsuario){
	this->colaDeEntradasUsuario.push(entradaUsuario);
}

void AplicacionServidor::activarJugador(int idMarioConectandose){
	juego->conectarJugador(idMarioConectandose);
}

void AplicacionServidor::desconectarJugador(int idJugador){
	juego->desconectarJugador(idJugador);
}


SDL_Rect* AplicacionServidor::obtenerRectCamara(){
	return &rectanguloCamara;
}

bool AplicacionServidor::tengoJugadores(map<int,Mario*> jugadores) const{
	int i = 0;
	bool hayAlguienConectado = false;
	while(i<cantJugadores && !hayAlguienConectado){
		if(jugadores[i]->estaConectado()){
			hayAlguienConectado = true;
		}
		i++;
	}
	return hayAlguienConectado;

}

void AplicacionServidor::moverCamara(const map<int,Mario*>& jugadores){
	SDL_Rect* rectanguloCamara = obtenerRectCamara();

	int posicionDelJugadorMasALaDerecha = 0;
	int posicionDelJugadorMasALaIzquierda = ANCHO_FONDO;

	bool sePuedeMoverLaCamara = true;
	Mario* jugador;

	for(auto const& parClaveJugador: jugadores){
		jugador = parClaveJugador.second;

		if(jugador->estaConectado() && jugador->obtenerPosicionX() <= rectanguloCamara->x) {
			sePuedeMoverLaCamara = false;
		}else if(jugador->estaConectado()){
			if(jugador->obtenerPosicionX() > posicionDelJugadorMasALaDerecha){
				posicionDelJugadorMasALaDerecha = jugador->obtenerPosicionX();
			}
			if(jugador->obtenerPosicionX() < posicionDelJugadorMasALaIzquierda){
				posicionDelJugadorMasALaIzquierda = jugador->obtenerPosicionX();
			}
		}
	}

	bool unJugadorEstaDelLadoDerechoDeLaPantalla = posicionDelJugadorMasALaDerecha > rectanguloCamara->x + (ancho_pantalla)/2;

	if(sePuedeMoverLaCamara && unJugadorEstaDelLadoDerechoDeLaPantalla){
		//MOVER CAMARA
		if(posicionDelJugadorMasALaIzquierda < posicionDelJugadorMasALaDerecha - ancho_pantalla/2){
			rectanguloCamara->x = posicionDelJugadorMasALaIzquierda;
		}else{
			rectanguloCamara->x = posicionDelJugadorMasALaDerecha - ancho_pantalla/2;
		}

		if( rectanguloCamara->x > ANCHO_FONDO - ancho_pantalla){
			rectanguloCamara->x = ANCHO_FONDO - ancho_pantalla;
		}

		for(auto const& parClaveJugador: jugadores){
			jugador = parClaveJugador.second;
			if((!jugador->estaConectado()) && (jugador->obtenerPosicionX()<=rectanguloCamara->x)){
				jugador->serArrastrado(rectanguloCamara->x-jugador->obtenerPosicionX());
			}

			int anchoJugador = jugador->obtenerSpite()->obtenerRectanguloActual().w;
			jugador->actualizarMaximoX(rectanguloCamara->x);
			jugador->actualizarMinimoX(rectanguloCamara->x + ancho_pantalla - anchoJugador*2);
		}
	}

	if( rectanguloCamara->x < 0 ){
		 rectanguloCamara->x = 0;
	}


}

AplicacionServidor::~AplicacionServidor(){
	delete juego;
}

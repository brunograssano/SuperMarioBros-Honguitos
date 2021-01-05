#include "AplicacionServidor.hpp"

#include <unistd.h>

#include <utility>


AplicacionServidor::AplicacionServidor(Servidor* server,list<Nivel*> niveles,int cantidadJugadores,int ancho_pantalla ,int  alto_pantalla){
	juego = Juego::getInstance(std::move(niveles),cantidadJugadores);
	cantJugadores = cantidadJugadores;
	terminoElJuego = false;
	comenzoElJuego = false;
	juegoInicializadoCorrectamente = false;
	log = Log::getInstance();
	servidor = server;
	this->camara = new Camara(alto_pantalla, ancho_pantalla);
}

info_partida_t AplicacionServidor::obtenerInfoPartida(map<int,string> mapaIDNombre,int IDJugador){
	Log::getInstance()->mostrarMensajeDeInfo("Se prepara la informacion de la partida para el jugador: " + mapaIDNombre[IDJugador]);
	info_partida_t info_partida;
	memset(&info_partida,0,sizeof(info_partida_t));

	info_partida.altoVentana =  camara->obtenerRectanguloCamara().h;
	info_partida.anchoVentana = camara->obtenerRectanguloCamara().w;
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




info_ronda_t AplicacionServidor::obtenerInfoRonda(map<int,string> mapaIDNombre){

	Log::getInstance()->mostrarAccion("Se prepara la informacion de la ronda para enviar.");

	info_ronda_t info_ronda;
	memset(&info_ronda,0,sizeof(info_ronda_t));

	info_ronda.mundo = juego->obtenerMundoActual();
	info_ronda.posXCamara = this->camara->obtenerRectanguloCamara().x;
	info_ronda.tiempoFaltante = this->juego->obtenerTiempoRestante();
	info_ronda.ganaron = juego->ganaron();
	info_ronda.perdieron = terminoElJuego && !juego->ganaron();

	list<Plataforma*> plataformas = juego->obtenerPlataformas();
	int numeroBloque = 0;
	for(auto const& plataforma: plataformas){
		list<bloque_t> bloques = plataforma->serializarPlataforma();

		for(auto const& bloque: bloques){
			if(camara->estaEnRangoVisible(bloque.posX) &&
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
		if(camara->estaEnRangoVisible(enemigo->obtenerPosicionX()) &&
		numeroEnemigo<MAX_ENEMIGOS){
			info_ronda.enemigos[numeroEnemigo] = enemigo->serializar();
			numeroEnemigo++;
		}
	}
	info_ronda.topeEnemigos = numeroEnemigo;

	int numeroMoneda = 0;
	list<Moneda*> monedas = juego->obtenerMonedas();
	for(auto const& moneda: monedas){
		if(camara->estaEnRangoVisible(moneda->obtenerPosicionX()) &&
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
        if(camara->estaEnRangoVisible(tuberia->obtenerPosicionX()) &&
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
			juego->actualizarModelo(camara);

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

AplicacionServidor::~AplicacionServidor(){
    delete camara;
	delete juego;
}

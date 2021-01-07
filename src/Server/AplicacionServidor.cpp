#include "AplicacionServidor.hpp"

#include <unistd.h>

#include <utility>


AplicacionServidor::AplicacionServidor(Servidor* server,list<Nivel*> niveles,int cantidadJugadores,int ancho_pantalla ,int  alto_pantalla){
	juego = Juego::getInstance(std::move(niveles),cantidadJugadores, alto_pantalla, ancho_pantalla);
	cantJugadores = cantidadJugadores;
	terminoElJuego = false;
	comenzoElJuego = false;
	juegoInicializadoCorrectamente = false;
	log = Log::getInstance();
	servidor = server;
}

info_partida_t AplicacionServidor::obtenerInfoPartida(map<int,string> mapaIDNombre,int IDJugador){
	Log::getInstance()->mostrarMensajeDeInfo("Se prepara la informacion de la partida para el jugador: " + mapaIDNombre[IDJugador]);
	return juego->obtenerInfoPartida(mapaIDNombre, IDJugador);
}

info_ronda_t AplicacionServidor::obtenerInfoRonda(map<int,string> mapaIDNombre){
	Log::getInstance()->mostrarAccion("Se prepara la informacion de la ronda para enviar.");
    return juego->obtenerInfoRonda(mapaIDNombre);
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
    juego->iniciar();
	while(!terminoElJuego || juego->hayConectados()){
	    contador->iniciar();
		if(!terminoElJuego){

			while(!colaDeEntradasUsuario.empty()){
				entrada_usuario_id_t parIDEntrada = colaDeEntradasUsuario.front();
				juego->actualizarJugador(parIDEntrada.id, parIDEntrada.entradas);
				colaDeEntradasUsuario.pop();
			}
			juego->actualizarModelo();

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

AplicacionServidor::~AplicacionServidor(){
	delete juego;
}

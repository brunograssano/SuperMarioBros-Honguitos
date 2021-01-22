#include "EscuchadorInfoPartidaInicial.hpp"
#include "src/Utils/log/Log.hpp"

EscuchadorInfoPartidaInicial::EscuchadorInfoPartidaInicial(int socket,Cliente* cliente){
	this->socket = socket;
	this->cliente = cliente;
	structPointer = &this->info_partida;
	bytes = sizeof(info_partida_t);
}

void EscuchadorInfoPartidaInicial::casoError(int resultado){
	Log::getInstance()->huboUnErrorSDL("Hubo un error al escuchar informacion inicial de la partida, se cierra el socket", to_string(errno));
	throw runtime_error("ErrorAlEscucharInformacionInicialDeLaPartida");
}

void EscuchadorInfoPartidaInicial::casoSocketCerrado(){
	Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion inicial de la partida, se cierra el socket");
	throw runtime_error("ErrorAlEscucharInformacionInicialDeLaPartida");
}

void EscuchadorInfoPartidaInicial::casoExitoso(){
	if(recibioInformacionPartidaValida()){
		cliente->empezarJuego(info_partida);
	}else{
		Log::getInstance()->mostrarMensajeDeInfo("Ocurrio el siguiente error al escuchar la informacion inicial de la partida: " + error);
	}
}

bool EscuchadorInfoPartidaInicial::recibioInformacionPartidaValida(){
	bool esValidaInfoPartida = true;

    if(info_partida.cantidadJugadores > 4 || info_partida.cantidadJugadores < 0){
		esValidaInfoPartida = false;
		error = string("La cantidad de jugadores recibida es menor a 1 o mayor a 4");
	}else if(info_partida.idPropio > 3 || info_partida.idPropio < 0){
		esValidaInfoPartida = false;
		error = string("El id propio recibido es menor a 0 o mayor a 3");
	}

	return esValidaInfoPartida;
}
#include "EscuchadorInfoPartidaInicial.hpp"

EscuchadorInfoPartidaInicial::EscuchadorInfoPartidaInicial(int socket,Cliente* cliente){
	this->socket = socket;
	this->cliente = cliente;
	structPointer = &this->info_partida;
	bytes = sizeof(info_partida_t);
}

void EscuchadorInfoPartidaInicial::casoError(int resultado){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	Log::getInstance()->huboUnErrorSDL("Hubo un error al escuchar informacion inicial de la partida, se cierra el socket", to_string(errno));
	pthread_mutex_unlock(&mutex);
	throw runtime_error("ErrorAlEscucharInformacionInicialDeLaPartida");
}

void EscuchadorInfoPartidaInicial::casoSocketCerrado(){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion inicial de la partida, se cierra el socket");
	pthread_mutex_unlock(&mutex);
	throw runtime_error("ErrorAlEscucharInformacionInicialDeLaPartida");
}

void EscuchadorInfoPartidaInicial::casoExitoso(){
	cliente->empezarJuego(info_partida);
}

EscuchadorInfoPartidaInicial::~EscuchadorInfoPartidaInicial(){
}

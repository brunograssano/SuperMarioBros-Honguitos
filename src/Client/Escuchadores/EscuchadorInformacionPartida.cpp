#include "EscuchadorInformacionPartida.hpp"

EscuchadorInformacionPartida::EscuchadorInformacionPartida(int socket, Cliente* cliente){
	this->socket = socket;
	this->cliente = cliente;
	structPointer = &this->info;
	bytes = sizeof(info_inicio_t);
}

void EscuchadorInformacionPartida::casoError(int resultado){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	Log::getInstance()->huboUnErrorSDL("Hubo un error al escuchar informacion de la partida, se cierra el socket", to_string(errno));
	pthread_mutex_unlock(&mutex);
	throw runtime_error("ErrorAlEscucharInformacionDeLaPartida");
}
void EscuchadorInformacionPartida::casoSocketCerrado(){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion de la partida, se cierra el socket");
	pthread_mutex_unlock(&mutex);
	throw runtime_error("ErrorAlEscucharInformacionDeLaPartida");
}
void EscuchadorInformacionPartida::casoExitoso(){
	this->cliente->recibirInformacionServidor(info);
}

EscuchadorInformacionPartida::~EscuchadorInformacionPartida(){}

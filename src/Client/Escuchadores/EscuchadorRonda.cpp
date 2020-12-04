#include "EscuchadorRonda.hpp"

EscuchadorRonda::EscuchadorRonda(int socket, Cliente* cliente){
	this->socket = socket;
	this->cliente = cliente;
	structPointer = &this->info_ronda;
	bytes = sizeof(info_ronda_t);
}

void EscuchadorRonda::casoError(int resultado){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	Log::getInstance()->huboUnErrorSDL("Hubo un error al escuchar informacion de la ronda, se cierra el socket", to_string(errno));
	pthread_mutex_unlock(&mutex);
	throw runtime_error("ErrorAlEscucharInformacionDeLaRonda");
}

void EscuchadorRonda::casoSocketCerrado(){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion de la ronda, se cierra el socket");
	pthread_mutex_unlock(&mutex);
	throw runtime_error("ErrorAlEscucharInformacionDeLaRonda");
}

void EscuchadorRonda::casoExitoso(){
	cliente->recibirInformacionRonda(info_ronda);
}

EscuchadorRonda::~EscuchadorRonda(){

}

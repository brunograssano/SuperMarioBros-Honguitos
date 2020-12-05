#include "EscuchadorActualizacionJugadores.hpp"

EscuchadorActualizacionJugadores::EscuchadorActualizacionJugadores(int socket, Cliente* cliente){
	this->socket = socket;
	this->cliente = cliente;
	structPointer = &this->actualizacion;
	bytes = sizeof(actualizacion_cantidad_jugadores_t);
}

void EscuchadorActualizacionJugadores::casoError(int resultado){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	Log::getInstance()->huboUnErrorSDL("Hubo un error al recibir la informacion de actualizacion de jugadores, se cierra el socket", to_string(errno));
	pthread_mutex_unlock(&mutex);
	throw runtime_error("ErrorAlEscucharActualizacionJugadores");
}
void EscuchadorActualizacionJugadores::casoSocketCerrado(){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion de actualizacion de jugadores, se cierra el socket");
	pthread_mutex_unlock(&mutex);
	throw runtime_error("ErrorAlEscucharActualizacionJugadores");
}
void EscuchadorActualizacionJugadores::casoExitoso(){
	this->cliente->recibirInformacionActualizacion(actualizacion);
}

EscuchadorActualizacionJugadores::~EscuchadorActualizacionJugadores(){

}

#include "EscuchadorVerificacionCredenciales.hpp"

EscuchadorVerificacionCredenciales::EscuchadorVerificacionCredenciales(int socket, Cliente* cliente){
	this->socket = socket;
	this->cliente = cliente;
	structPointer = &this->verificacion;
	bytes = sizeof(verificacion_t);
}

void EscuchadorVerificacionCredenciales::casoError(int resultado){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	Log::getInstance()->huboUnErrorSDL("Hubo un error al escuchar informacion de la verificacion de las credenciales, se cierra el socket", to_string(errno));
	pthread_mutex_unlock(&mutex);
	throw runtime_error("ErrorAlVerificarCredenciales");
}

void EscuchadorVerificacionCredenciales::casoSocketCerrado(){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion inicial de la partida, se cierra el socket");
	pthread_mutex_unlock(&mutex);
	throw runtime_error("ErrorAlVerificarCredenciales");
}

void EscuchadorVerificacionCredenciales::casoExitoso(){
	this->cliente->recibirVerificacionCredenciales(verificacion);
}

EscuchadorVerificacionCredenciales::~EscuchadorVerificacionCredenciales(){

}

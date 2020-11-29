#include "EscuchadorVerificacionCredenciales.hpp"

EscuchadorVerificacionCredenciales::EscuchadorVerificacionCredenciales(int socket, Cliente* cliente){
	this->socket = socket;
	this->cliente = cliente;
}

void EscuchadorVerificacionCredenciales::escuchar(){
	verificacion_t verificacion;
	int resultado = recv(socket, &verificacion, sizeof(verificacion_t), MSG_WAITALL);
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	if(resultado<0){
		pthread_mutex_lock(&mutex);
		Log::getInstance()->huboUnErrorSDL("Hubo un error al escuchar informacion de la verificacion de las credenciales, se cierra el socket", to_string(errno));
		pthread_mutex_unlock(&mutex);
		throw runtime_error("ErrorAlVerificarCredenciales");
	}else if(resultado == 0){
		pthread_mutex_lock(&mutex);
		Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion inicial de la partida, se cierra el socket");
		pthread_mutex_unlock(&mutex);
		throw runtime_error("ErrorAlVerificarCredenciales");
	}

	this->cliente->recibirVerificacionCredenciales(verificacion);
}

EscuchadorVerificacionCredenciales::~EscuchadorVerificacionCredenciales(){
}

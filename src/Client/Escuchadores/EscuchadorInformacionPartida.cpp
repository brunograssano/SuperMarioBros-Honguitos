#include "EscuchadorInformacionPartida.hpp"

EscuchadorInformacionPartida::EscuchadorInformacionPartida(int socket, Cliente* cliente){
	this->socket = socket;
	this->cliente = cliente;
}

void EscuchadorInformacionPartida::escuchar(){
	info_inicio_t info;
	int resultado = recv(socket, &info, sizeof(info_inicio_t), MSG_WAITALL);
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	if(resultado<0){
		pthread_mutex_lock(&mutex);
		Log::getInstance()->huboUnErrorSDL("Hubo un error al escuchar informacion de la partida, se cierra el socket", to_string(errno));
		pthread_mutex_unlock(&mutex);
		throw runtime_error("ErrorAlEscucharInformacionDeLaPartida");
	}else if(resultado == 0){
		pthread_mutex_lock(&mutex);
		Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion de la partida, se cierra el socket");
		pthread_mutex_unlock(&mutex);
		throw runtime_error("ErrorAlEscucharInformacionDeLaPartida");
	}

	this->cliente->recibirInformacionServidor(info);
}

EscuchadorInformacionPartida::~EscuchadorInformacionPartida(){
}

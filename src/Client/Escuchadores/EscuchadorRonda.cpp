#include "EscuchadorRonda.hpp"



EscuchadorRonda::EscuchadorRonda(int socket, Cliente* cliente){
	this->socket = socket;
	this->cliente = cliente;
}

void EscuchadorRonda::escuchar(){

	info_ronda_t info_ronda;
	int resultado = recv(socket,&info_ronda,sizeof(info_ronda_t),MSG_WAITALL);
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	if(resultado<0){
		pthread_mutex_lock(&mutex);
		Log::getInstance()->huboUnErrorSDL("Hubo un error al escuchar informacion de la ronda, se cierra el socket", to_string(errno));
		pthread_mutex_unlock(&mutex);
		throw runtime_error("ErrorAlEscucharInformacionDeLaRonda");
	}else if(resultado == 0){
		pthread_mutex_lock(&mutex);
		Log::getInstance()->mostrarMensajeDeInfo("No se recibió más información de la ronda, se cierra el socket");
		pthread_mutex_unlock(&mutex);
		throw runtime_error("ErrorAlEscucharInformacionDeLaRonda");
	}

	cliente->recibirInformacionRonda(info_ronda);
}

EscuchadorRonda::~EscuchadorRonda(){

}

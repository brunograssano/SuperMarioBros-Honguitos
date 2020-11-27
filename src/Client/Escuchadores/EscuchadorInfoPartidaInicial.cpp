
#include "EscuchadorInfoPartidaInicial.hpp"

EscuchadorInfoPartidaInicial::EscuchadorInfoPartidaInicial(int socket,Cliente* cliente){
	this->socket = socket;
	this->cliente = cliente;
}

void EscuchadorInfoPartidaInicial::escuchar(){
	info_partida_t info_partida;
	int resultado = recv(socket,&info_partida,sizeof(info_partida_t),MSG_WAITALL);
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	if(resultado<0){
		pthread_mutex_lock(&mutex);
		Log::getInstance()->huboUnErrorSDL("Hubo un error al escuchar informacion inicial de la partida, se cierra el socket", to_string(errno));
		pthread_mutex_unlock(&mutex);
		throw runtime_error("ErrorAlEscucharInformacionInicialDeLaPartida");
	}else if(resultado == 0){
		pthread_mutex_lock(&mutex);
		Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion inicial de la partida, se cierra el socket");
		pthread_mutex_unlock(&mutex);
		throw runtime_error("ErrorAlEscucharInformacionInicialDeLaPartida");
	}

	cliente->empezarJuego(info_partida);
}

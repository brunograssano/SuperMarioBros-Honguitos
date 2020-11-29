#include "EscuchadorActualizacionJugadores.hpp"

EscuchadorActualizacionJugadores::EscuchadorActualizacionJugadores(int socket, Cliente* cliente){
	this->socket = socket;
	this->cliente = cliente;
}

void EscuchadorActualizacionJugadores::escuchar(){


	actualizacion_cantidad_jugadores_t actualizacion;
	int resultado = recv(socket, &actualizacion, sizeof(actualizacion_cantidad_jugadores_t), MSG_WAITALL);
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	if(resultado<0){
		pthread_mutex_lock(&mutex);
		Log::getInstance()->huboUnErrorSDL("Hubo un error al recibir la informacion de actualizacion de jugadores, se cierra el socket", to_string(errno));
		pthread_mutex_unlock(&mutex);
		throw runtime_error("ErrorAlEscucharActualizacionJugadores");
	}else if(resultado == 0){
		pthread_mutex_lock(&mutex);
		Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion de actualizacion de jugadores, se cierra el socket");
		pthread_mutex_unlock(&mutex);
		throw runtime_error("ErrorAlEscucharActualizacionJugadores");
	}

	this->cliente->recibirInformacionActualizacionCantidadJugadores(actualizacion.cantidadJugadoresActivos);
}

EscuchadorActualizacionJugadores::~EscuchadorActualizacionJugadores(){
}

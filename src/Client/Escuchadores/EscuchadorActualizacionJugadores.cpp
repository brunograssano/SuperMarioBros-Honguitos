#include "EscuchadorActualizacionJugadores.hpp"

EscuchadorActualizacionJugadores::EscuchadorActualizacionJugadores(int socket, Cliente* cliente){
	this->socket = socket;
	this->cliente = cliente;
}

void EscuchadorActualizacionJugadores::escuchar(){


	actualizacion_cantidad_jugadores_t actualizacion;
	int result = recv(socket, &actualizacion, sizeof(actualizacion_cantidad_jugadores_t), MSG_WAITALL);
	//TODO: Si result = 0 -> hay que matar al cliente. 'delete cliente' ¿?
	this->cliente->recibirInformacionActualizacionCantidadJugadores(actualizacion.cantidadJugadoresActivos);
}

EscuchadorActualizacionJugadores::~EscuchadorActualizacionJugadores(){
}

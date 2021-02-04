
#include "EnviadorCantidadConexion.hpp"

EnviadorCantidadConexion::EnviadorCantidadConexion(int socket){
	this->socket = socket;
	memset(&actualizacion,0,sizeof(actualizacion_cantidad_jugadores_t));
}

void EnviadorCantidadConexion::enviar(){
    Enviador::enviar(ACTUALIZACION_JUGADORES,&actualizacion,sizeof(actualizacion_cantidad_jugadores_t));
}

void EnviadorCantidadConexion::dejarInformacion(void* nueva_actualizacion){
	this->actualizacion = *((actualizacion_cantidad_jugadores_t*) nueva_actualizacion);
}



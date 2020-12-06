
#include "EnviadorCantidadConexion.hpp"

EnviadorCantidadConexion::EnviadorCantidadConexion(int socket){
	this->socket = socket;
}

void EnviadorCantidadConexion::enviar(){
	char caracterMensaje = ACTUALIZACION_JUGADORES;
	int resultadoEnvio;

	resultadoEnvio = send(socket, &caracterMensaje, sizeof(char), 0);
	this->revisarSiSeMandoCorrectamente(resultadoEnvio, "el caracter de actualizacion de cantidad de jugadores");

	resultadoEnvio = send(socket, &actualizacion, sizeof(actualizacion_cantidad_jugadores_t), 0);
	this->revisarSiSeMandoCorrectamente(resultadoEnvio, "la estructura de actualizacion de cantidad de jugaores");
}

void EnviadorCantidadConexion::dejarInformacion(void* actualizacion){
	this->actualizacion = *((actualizacion_cantidad_jugadores_t*) actualizacion);
}



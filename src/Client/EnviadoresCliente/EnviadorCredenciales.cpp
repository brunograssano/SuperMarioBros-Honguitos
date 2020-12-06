

#include "EnviadorCredenciales.hpp"

EnviadorCredenciales::EnviadorCredenciales(int socket){
	this->socket = socket;
	memset(&credenciales,0,sizeof(credencial_t));
}

void EnviadorCredenciales::enviar(){
	char tipoMensaje = CREDENCIAL;

	int resultadoEnvio = send(socket, &tipoMensaje, sizeof(char), 0);
	this->revisarSiSeMandoCorrectamente(resultadoEnvio, "el caracter de informacion de credencial");

	resultadoEnvio = send(socket, &credenciales, sizeof(credencial_t), 0);
	this->revisarSiSeMandoCorrectamente(resultadoEnvio, "la estructura de credencial");
}

void EnviadorCredenciales::dejarInformacion(void* informacion){
	credenciales = *((credencial_t*)informacion);
}





#include "EnviadorCredenciales.hpp"

EnviadorCredenciales::EnviadorCredenciales(int socket){
	this->socket = socket;
}

void EnviadorCredenciales::enviar(){
	char tipoMensaje = CREDENCIAL;
	send(socket, &tipoMensaje, sizeof(char), 0);
	send(socket, &credenciales, sizeof(credencial_t), 0);
}

void EnviadorCredenciales::dejarInformacion(void* informacion){
	credenciales = *((credencial_t*)informacion);
}



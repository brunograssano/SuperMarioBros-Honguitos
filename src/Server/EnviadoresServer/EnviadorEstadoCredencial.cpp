
#include "EnviadorEstadoCredencial.hpp"


EnviadorEstadoCredencial::EnviadorEstadoCredencial(int socket){
	this->socket = socket;
	estadoCredencial = false;
}

void EnviadorEstadoCredencial::enviar(){
	char caracterMensaje = VERIFICACION;
	send(socket, &caracterMensaje, sizeof(char), 0);
	send(socket, &estadoCredencial , sizeof(verificacion_t), 0);
}

void EnviadorEstadoCredencial::dejarInformacion(void* estadoDeLaCredencial){
	estadoCredencial =  *((verificacion_t*) estadoDeLaCredencial);
}



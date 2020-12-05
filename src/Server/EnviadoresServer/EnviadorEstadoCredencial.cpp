
#include "EnviadorEstadoCredencial.hpp"


EnviadorEstadoCredencial::EnviadorEstadoCredencial(int socket){
	this->socket = socket;
	estadoCredencial = false;
}

void EnviadorEstadoCredencial::enviar(){
	char caracterMensaje = VERIFICACION;
	int resultadoEnvio;
	resultadoEnvio = send(socket, &caracterMensaje, sizeof(char), 0);
	this->revisarSiSeMandoCorrectamente(resultadoEnvio, "el caracter de verificacion de credencial");

	resultadoEnvio = send(socket, &estadoCredencial , sizeof(verificacion_t), 0);
	this->revisarSiSeMandoCorrectamente(resultadoEnvio, "la estructura de verificacion de credencial");
}

void EnviadorEstadoCredencial::dejarInformacion(void* estadoDeLaCredencial){
	estadoCredencial =  *((verificacion_t*) estadoDeLaCredencial);
}



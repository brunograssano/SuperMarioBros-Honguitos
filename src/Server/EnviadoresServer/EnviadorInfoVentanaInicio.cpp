
#include "EnviadorInfoVentanaInicio.hpp"


EnviadorInfoVentanaInicio::EnviadorInfoVentanaInicio(int socket){
	this->socket = socket;
}

void EnviadorInfoVentanaInicio::enviar(){
	char caracterMensaje = INICIO;

	int resultadoEnvio;
	resultadoEnvio = send(socket, &caracterMensaje, sizeof(char), 0);
	this->revisarSiSeMandoCorrectamente(resultadoEnvio, "el caracter de informacion de la ventana de incicio");


	resultadoEnvio = send(socket, &info_inicio_ventana, sizeof(info_inicio_t), 0);
	this->revisarSiSeMandoCorrectamente(resultadoEnvio, "la estructura de informacion de la ventana de inicio");
};

void EnviadorInfoVentanaInicio::dejarInformacion(void* infoComienzoPartida){
	info_inicio_ventana = *((info_inicio_t*) infoComienzoPartida);
};



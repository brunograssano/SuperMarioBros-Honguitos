
#include "EnviadorInfoPartida.hpp"
#include <string.h>


EnviadorInfoPartida::EnviadorInfoPartida(int socket){
	this->socket = socket;
	memset(&info_comienzo_partida,0,sizeof(info_partida_t));
}


void EnviadorInfoPartida::enviar(){
	char caracterMensaje = MENSAJE_LOG;
	mensaje_log_t mensaje={0,0};
	mensaje.tipo = INFO;
	strcpy(mensaje.mensajeParaElLog,"Empieza el juego...");

	int resultadoEnvio;
	resultadoEnvio = send(socket, &caracterMensaje, sizeof(char), 0);
	this->revisarSiSeMandoCorrectamente(resultadoEnvio, "el caracter de mensaje para log");

	resultadoEnvio = send(socket, &mensaje, sizeof(mensaje_log_t), 0);
	this->revisarSiSeMandoCorrectamente(resultadoEnvio, "el mensaje de inicio de juego");

	caracterMensaje = PARTIDA;
	resultadoEnvio = send(socket, &caracterMensaje, sizeof(char), 0);
	this->revisarSiSeMandoCorrectamente(resultadoEnvio, "el caracter de informacion de partida");

	resultadoEnvio = send(socket, &info_comienzo_partida, sizeof(info_partida_t), 0);
	this->revisarSiSeMandoCorrectamente(resultadoEnvio, "la estructura de informacion de partida");
}

void EnviadorInfoPartida::dejarInformacion(void* infoComienzoPartida){
	info_comienzo_partida = *((info_partida_t*)infoComienzoPartida);
}


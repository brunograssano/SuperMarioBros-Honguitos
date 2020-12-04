
#include "EnviadorInfoPartida.hpp"
#include <string.h>


EnviadorInfoPartida::EnviadorInfoPartida(int socket){
	this->socket = socket;
}


void EnviadorInfoPartida::enviar(){
	char caracterMensaje = MENSAJE_LOG;
	mensaje_log_t mensaje={0,0};
	mensaje.tipo = INFO;
	strcpy(mensaje.mensajeParaElLog,"Empieza el juego...");
	send(socket, &caracterMensaje, sizeof(char), 0);
	send(socket, &mensaje, sizeof(mensaje_log_t), 0);

	caracterMensaje = PARTIDA;
	send(socket, &caracterMensaje, sizeof(char), 0);
	send(socket, &info_comienzo_partida, sizeof(info_partida_t), 0);
}

void EnviadorInfoPartida::dejarInformacion(void* infoComienzoPartida){
	info_comienzo_partida = *((info_partida_t*)infoComienzoPartida);
}

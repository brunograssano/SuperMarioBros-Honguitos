#include "EnviadorInfoPartida.hpp"
#include <cstring>

EnviadorInfoPartida::EnviadorInfoPartida(Socket* socket){
	this->socket = socket;
	memset(&info_comienzo_partida,0,sizeof(info_partida_t));
}


void EnviadorInfoPartida::enviar(){
	mensaje_log_t mensaje={0,{0}};
	mensaje.tipo = INFO;
	strcpy(mensaje.mensajeParaElLog,"Empieza el juego...");

    Enviador::enviar(MENSAJE_LOG,&mensaje,sizeof(mensaje_log_t));
    Enviador::enviar(PARTIDA,&info_comienzo_partida,sizeof(info_partida_t));
}

void EnviadorInfoPartida::dejarInformacion(void* infoComienzoPartida){
	info_comienzo_partida = *((info_partida_t*)infoComienzoPartida);
}



#include "EscuchadorInfoPartidaInicial.hpp"

EscuchadorInfoPartidaInicial::EscuchadorInfoPartidaInicial(int socket,Cliente* cliente){
	this->socket = socket;
	this->cliente = cliente;
}

void EscuchadorInfoPartidaInicial::escuchar(){
	info_partida_t info_partida;
	int resultado = recv(socket,&info_partida,sizeof(info_partida_t),MSG_WAITALL);
	//IF RESULTADO<0 TODO

	cliente->empezarJuego(info_partida);
}

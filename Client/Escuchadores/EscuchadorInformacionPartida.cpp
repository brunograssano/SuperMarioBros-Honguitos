#include "EscuchadorInformacionPartida.hpp"

EscuchadorInformacionPartida::EscuchadorInformacionPartida(int socket, Cliente* cliente){
	this->socket = socket;
	this->cliente = cliente;
}

void EscuchadorInformacionPartida::escuchar(){
	info_inicio_t info;
	int result = recv(socket, &info, sizeof(info_inicio_t), MSG_WAITALL);
	//TODO: Si result = 0 -> hay que matar al cliente. 'delete cliente' ¿?
	this->cliente->recibirInformacionServidor(info);
}



EscuchadorInformacionPartida::~EscuchadorInformacionPartida(){
}

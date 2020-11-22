#include "EscuchadorVerificacionCredenciales.hpp"

EscuchadorVerificacionCredenciales::EscuchadorVerificacionCredenciales(int socket, Cliente* cliente){
	this->socket = socket;
	this->cliente = cliente;
}

void EscuchadorVerificacionCredenciales::escuchar(){
	verificacion_t verificacion;
	int result = recv(socket, &verificacion, sizeof(verificacion_t), MSG_WAITALL);
	//TODO: Si result = 0 -> hay que matar al cliente. 'delete cliente' ¿?
	this->cliente->recibirVerificacionCredenciales(verificacion);
}

EscuchadorVerificacionCredenciales::~EscuchadorVerificacionCredenciales(){
}

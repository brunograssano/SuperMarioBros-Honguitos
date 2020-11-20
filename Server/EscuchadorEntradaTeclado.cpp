
#include "EscuchadorEntradaTeclado.hpp"

EscuchadorEntradaTeclado::EscuchadorEntradaTeclado(int socket, int idJugador, Servidor* servidor){
	this->idJugador = idJugador;
	this->socket = socket;
	this->servidor = servidor;
}

void EscuchadorEntradaTeclado::escuchar(){

	entrada_usuario_t entradaUsuario;
	entrada_usuario_id_t entradaUsuarioId;

	recv(socket, &entradaUsuario, sizeof(entrada_usuario_t), MSG_WAITALL);

	entradaUsuarioId.entradas = entradaUsuario;
	entradaUsuarioId.id = idJugador;

	servidor->encolarEntradaUsuario(entradaUsuarioId);
}

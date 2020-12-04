
#include "EnviadorEntrada.hpp"

EnviadorEntrada::EnviadorEntrada(int socket){
	this->socket = socket;
}

void EnviadorEntrada::enviar(){
	entrada_usuario_t entrada;
	char tipo = ENTRADA;
	if(!entradasUsuario.empty()){
		entrada = entradasUsuario.front();
		entradasUsuario.pop();

		send(socket,&tipo,sizeof(char),0);
		send(socket,&entrada,sizeof(entrada_usuario_t),0);
	}

}
void EnviadorEntrada::dejarInformacion(void* informacion){
	entradasUsuario.push(*((entrada_usuario_t*)informacion));
}




#include "EnviadorEntrada.hpp"

EnviadorEntrada::EnviadorEntrada(int socket){
	this->socket = socket;
}

void EnviadorEntrada::enviar(){
	entrada_usuario_t entrada;
	char tipo = ENTRADA;
	int resultadoEnvio;
	if(!entradasUsuario.empty()){
		entrada = entradasUsuario.front();
		entradasUsuario.pop();


		resultadoEnvio = send(socket,&tipo,sizeof(char),0);
		this->revisarSiSeMandoCorrectamente(resultadoEnvio, "el caracter de entrada de usuario");
		resultadoEnvio = send(socket,&entrada,sizeof(entrada_usuario_t),0);
		this->revisarSiSeMandoCorrectamente(resultadoEnvio, "la estructura de entrada de un usuario");
	}

}
void EnviadorEntrada::dejarInformacion(void* informacion){
	entradasUsuario.push(*((entrada_usuario_t*)informacion));
}



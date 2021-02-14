#include "EnviadorRonda.hpp"

EnviadorRonda::EnviadorRonda(Socket* socket){
	this->socket = socket;
}

void EnviadorRonda::enviar(){
	info_ronda_t ronda;
	memset(&ronda,0,sizeof(info_ronda_t));
	if(!colaRondas.empty()){
		ronda = colaRondas.front();
		colaRondas.pop();
		Enviador::enviar(RONDA,&ronda,sizeof(info_ronda_t));
	}
}

void EnviadorRonda::dejarInformacion(void* mensajeLog){
	colaRondas.push(*((info_ronda_t*) mensajeLog));
}


#include "EnviadorRonda.hpp"

EnviadorRonda::EnviadorRonda(int socket){
	this->socket = socket;
}

void EnviadorRonda::enviar(){
	char caracterMensaje = RONDA;
	info_ronda_t ronda;
	memset(&ronda,0,sizeof(info_ronda_t));
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	int resultadoEnvio = 0;;

	if(!colaRondas.empty()){
		pthread_mutex_lock(&mutex);
		ronda = colaRondas.front();
		colaRondas.pop();
		resultadoEnvio = send(socket, &caracterMensaje, sizeof(char), 0);
		this->revisarSiSeMandoCorrectamente(resultadoEnvio, "el caracter de mensaje de ronda");
		resultadoEnvio = send(socket, &ronda, sizeof(info_ronda_t), 0);
		this->revisarSiSeMandoCorrectamente(resultadoEnvio, "la estructura de informacion de una ronda");
		pthread_mutex_unlock(&mutex);
	}
};

void EnviadorRonda::dejarInformacion(void* mensajeLog){
	colaRondas.push(*((info_ronda_t*) mensajeLog));
};

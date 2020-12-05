
#include "EnviadorRonda.hpp"

EnviadorRonda::EnviadorRonda(int socket){
	this->socket = socket;
}

void EnviadorRonda::enviar(){
	char caracterMensaje = RONDA;
	info_ronda_t ronda;
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	if(!colaRondas.empty()){
		pthread_mutex_lock(&mutex);
		ronda = colaRondas.front();
		colaRondas.pop();
		send(socket, &caracterMensaje, sizeof(char), 0);
		send(socket, &ronda, sizeof(info_ronda_t), 0);
		pthread_mutex_unlock(&mutex);
	}
};

void EnviadorRonda::dejarInformacion(void* mensajeLog){
	colaRondas.push(*((info_ronda_t*) mensajeLog));
};

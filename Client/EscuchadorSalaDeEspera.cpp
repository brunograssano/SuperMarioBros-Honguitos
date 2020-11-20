#include "EscuchadorSalaDeEspera.hpp"

#include <thread>

EscuchadorSalaDeEspera::EscuchadorSalaDeEspera(int socket){
	this->socket = socket;
	this->cantidadConectados = 0;
}

void EscuchadorSalaDeEspera::escuchar(){
	int buffer;
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	while(true){
		int result = recv(this->socket, &buffer, sizeof(buffer), MSG_WAITALL);
		pthread_mutex_lock(&mutex);
		this->cantidadConectados = buffer;
		pthread_mutex_unlock(&mutex);
	}
}

int EscuchadorSalaDeEspera::getCantidadConectados(){
	return this->cantidadConectados;
}

EscuchadorSalaDeEspera::~EscuchadorSalaDeEspera(){}

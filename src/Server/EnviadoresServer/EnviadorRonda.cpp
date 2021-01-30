#include "EnviadorRonda.hpp"
pthread_mutex_t mutexRonda = PTHREAD_MUTEX_INITIALIZER;

EnviadorRonda::EnviadorRonda(Socket* socket){
	this->socket = socket;
}

void EnviadorRonda::enviar(){
	info_ronda_t ronda;
	memset(&ronda,0,sizeof(info_ronda_t));
	if(!colaRondas.empty()){
		pthread_mutex_lock(&mutexRonda);
		ronda = colaRondas.front();
		colaRondas.pop();
		pthread_mutex_unlock(&mutexRonda);
		Enviador::enviar(RONDA,&ronda,sizeof(info_ronda_t));
	}
}

void EnviadorRonda::dejarInformacion(void* mensajeLog){
	pthread_mutex_lock(&mutexRonda);
	colaRondas.push(*((info_ronda_t*) mensajeLog));
	pthread_mutex_unlock(&mutexRonda);
}

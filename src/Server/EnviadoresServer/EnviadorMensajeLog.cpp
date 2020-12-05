

#include "EnviadorMensajeLog.hpp"

EnviadorMensajeLog::EnviadorMensajeLog(int socket){
	this->socket = socket;
}


void EnviadorMensajeLog::enviar(){
	char caracterMensaje = MENSAJE_LOG;
	mensaje_log_t mensaje;
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	if(!mensajesLog.empty()){
		pthread_mutex_lock(&mutex);
		mensaje = mensajesLog.front();
		mensajesLog.pop();
		send(socket, &caracterMensaje, sizeof(char), 0);
		send(socket, &mensaje, sizeof(info_ronda_t), 0);
		pthread_mutex_unlock(&mutex);
	}

}

void EnviadorMensajeLog::dejarInformacion(void* informacion){
	mensajesLog.push(*((mensaje_log_t*)informacion));
}

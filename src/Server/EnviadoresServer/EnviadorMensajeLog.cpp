#include "EnviadorMensajeLog.hpp"

EnviadorMensajeLog::EnviadorMensajeLog(int socket){
	this->socket = socket;
}

void EnviadorMensajeLog::enviar(){
	mensaje_log_t mensaje;
	memset(&mensaje,0,sizeof(mensaje_log_t));
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	if(!mensajesLog.empty()){
		pthread_mutex_lock(&mutex);
		mensaje = mensajesLog.front();
		mensajesLog.pop();
		pthread_mutex_unlock(&mutex);
        Enviador::enviar(MENSAJE_LOG,&mensaje,sizeof(mensaje_log_t));
	}

}

void EnviadorMensajeLog::dejarInformacion(void* informacion){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	mensajesLog.push(*((mensaje_log_t*)informacion));
	pthread_mutex_unlock(&mutex);
}

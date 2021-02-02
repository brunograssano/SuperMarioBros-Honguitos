#include "EnviadorMensajeLog.hpp"
pthread_mutex_t mutexLog = PTHREAD_MUTEX_INITIALIZER;

EnviadorMensajeLog::EnviadorMensajeLog(Socket* socket){
	this->socket = socket;
}

void EnviadorMensajeLog::enviar(){
	mensaje_log_t mensaje;
	memset(&mensaje,0,sizeof(mensaje_log_t));
	if(!mensajesLog.empty()){
		pthread_mutex_lock(&mutexLog);
		mensaje = mensajesLog.front();
		mensajesLog.pop();
		pthread_mutex_unlock(&mutexLog);
        Enviador::enviar(MENSAJE_LOG,&mensaje,sizeof(mensaje_log_t));
	}

}

void EnviadorMensajeLog::dejarInformacion(void* informacion){
	pthread_mutex_lock(&mutexLog);
	mensajesLog.push(*((mensaje_log_t*)informacion));
	pthread_mutex_unlock(&mutexLog);
}

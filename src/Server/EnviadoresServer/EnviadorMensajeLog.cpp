

#include "EnviadorMensajeLog.hpp"

EnviadorMensajeLog::EnviadorMensajeLog(int socket){
	this->socket = socket;
}


void EnviadorMensajeLog::enviar(){
	char caracterMensaje = MENSAJE_LOG;
	mensaje_log_t mensaje;
	memset(&mensaje,0,sizeof(mensaje_log_t));
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	int resultadoEnvio = 0;

	if(!mensajesLog.empty()){
		pthread_mutex_lock(&mutex);
		mensaje = mensajesLog.front();
		mensajesLog.pop();
		pthread_mutex_unlock(&mutex);

		resultadoEnvio = send(socket, &caracterMensaje, sizeof(char), 0);
		this->revisarSiSeMandoCorrectamente(resultadoEnvio, "el caracter de mensaje para el log");

		resultadoEnvio = send(socket, &mensaje, sizeof(mensaje_log_t), 0);
		this->revisarSiSeMandoCorrectamente(resultadoEnvio, "la estructura de mensaje de informacion de ronda");

	}

}

void EnviadorMensajeLog::dejarInformacion(void* informacion){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	mensajesLog.push(*((mensaje_log_t*)informacion));
	pthread_mutex_unlock(&mutex);
}



#include "EnviadorMensajeLog.hpp"

EnviadorMensajeLog::EnviadorMensajeLog(int socket){
	this->socket = socket;
}


void EnviadorMensajeLog::enviar(){
	char caracterMensaje = MENSAJE_LOG;
	mensaje_log_t mensaje;
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	int resultadoEnvio;
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
	mensajesLog.push(*((mensaje_log_t*)informacion));
}

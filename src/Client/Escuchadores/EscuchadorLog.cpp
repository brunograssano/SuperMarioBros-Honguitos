#include "EscuchadorLog.hpp"


EscuchadorLog::EscuchadorLog(int socket){
	this->socket = socket;
	strcpy(conjuntoMensajeLog.mensajeParaElLog,"");
	conjuntoMensajeLog.tipo = ' ';
	structPointer = &this->conjuntoMensajeLog;
	bytes = sizeof(mensaje_log_t);
}


void EscuchadorLog::casoError(int resultado){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	Log::getInstance()->huboUnErrorSDL("Ocurrio un error al recibir un mensaje del log", to_string(errno));
	pthread_mutex_unlock(&mutex);
	throw runtime_error("ErrorAlEscucharUnMensajeParaElLog");
}

void EscuchadorLog::casoSocketCerrado(){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion del mensaje para el Log. Se cierra el socket.");
	pthread_mutex_unlock(&mutex);
	throw runtime_error("ErrorAlEscucharMensajeDelLog");
}

void EscuchadorLog::casoExitoso(){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	string mensajeLog(conjuntoMensajeLog.mensajeParaElLog);
	if(conjuntoMensajeLog.tipo == TIPO_ERROR){
		pthread_mutex_lock(&mutex);
		Log::getInstance()->huboUnError(mensajeLog);
		pthread_mutex_unlock(&mutex);
	}
	else if(conjuntoMensajeLog.tipo == INFO){
		pthread_mutex_lock(&mutex);
		Log::getInstance()->mostrarMensajeDeInfo(mensajeLog);
		pthread_mutex_unlock(&mutex);
	}
}

#include "EnviadorMensajeLog.hpp"

EnviadorMensajeLog::EnviadorMensajeLog(Socket* socket){
	this->socket = socket;
}

void EnviadorMensajeLog::enviar(){
	mensaje_log_t mensaje;
	memset(&mensaje,0,sizeof(mensaje_log_t));
	if(!mensajesLog.empty()){
		mensaje = mensajesLog.front();
		mensajesLog.pop();
        Enviador::enviar(MENSAJE_LOG,&mensaje,sizeof(mensaje_log_t));
	}

}

void EnviadorMensajeLog::dejarInformacion(void* informacion){
	mensajesLog.push(*((mensaje_log_t*)informacion));
}

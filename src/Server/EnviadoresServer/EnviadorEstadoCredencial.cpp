
#include "EnviadorEstadoCredencial.hpp"


EnviadorEstadoCredencial::EnviadorEstadoCredencial(int socket){
	this->socket = socket;
	estadoCredencial = false;
	memset(&estadoCredencial,0,sizeof(verificacion_t));
}

void EnviadorEstadoCredencial::enviar(){
    Enviador::enviar(VERIFICACION,&estadoCredencial,sizeof(verificacion_t));
}

void EnviadorEstadoCredencial::dejarInformacion(void* estadoDeLaCredencial){
	estadoCredencial =  *((verificacion_t*) estadoDeLaCredencial);
}



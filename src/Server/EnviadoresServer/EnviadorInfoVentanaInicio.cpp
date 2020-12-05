
#include "EnviadorInfoVentanaInicio.hpp"


EnviadorInfoVentanaInicio::EnviadorInfoVentanaInicio(int socket){
	this->socket = socket;
}

void EnviadorInfoVentanaInicio::enviar(){
	char caracterMensaje = INICIO;
	send(socket, &caracterMensaje, sizeof(char), 0);
	send(socket, &info_inicio_ventana, sizeof(info_inicio_t), 0);
};

void EnviadorInfoVentanaInicio::dejarInformacion(void* infoComienzoPartida){
	info_inicio_ventana = *((info_inicio_t*) infoComienzoPartida);
};



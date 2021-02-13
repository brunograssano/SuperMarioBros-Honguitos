#include "src/Utils/Utils.hpp"
#include "EnviadorCredenciales.hpp"

EnviadorCredenciales::EnviadorCredenciales(Socket* socket){
	this->socket = socket;
	memset(&credenciales,0,sizeof(credencial_t));
}

void EnviadorCredenciales::enviar(){
	Enviador::enviar(CREDENCIAL,&credenciales,sizeof(credencial_t));
}

void EnviadorCredenciales::dejarInformacion(void* informacion){
	credenciales = *((credencial_t*)informacion);
}



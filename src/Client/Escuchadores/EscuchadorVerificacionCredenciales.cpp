#include "EscuchadorVerificacionCredenciales.hpp"
#include "src/Utils/log/Log.hpp"

EscuchadorVerificacionCredenciales::EscuchadorVerificacionCredenciales(int socket, Cliente* cliente){
	this->socket = socket;
	this->cliente = cliente;
	structPointer = &this->verificacion;
	bytes = sizeof(verificacion_t);
}

void EscuchadorVerificacionCredenciales::casoError(int resultado){
	Log::getInstance()->huboUnErrorSDL("Hubo un error al escuchar informacion de la verificacion de las credenciales, se cierra el socket", to_string(errno));
	throw runtime_error("ErrorAlVerificarCredenciales");
}

void EscuchadorVerificacionCredenciales::casoSocketCerrado(){
	Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion inicial de la partida, se cierra el socket");
	throw runtime_error("ErrorAlVerificarCredenciales");
}

void EscuchadorVerificacionCredenciales::casoExitoso(){
	this->cliente->recibirVerificacionCredenciales(verificacion);
}

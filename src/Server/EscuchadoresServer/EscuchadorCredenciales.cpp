#include "EscuchadorCredenciales.hpp"

EscuchadorCredenciales::EscuchadorCredenciales(int socket, ConexionCliente* cliente){
	this->socket = socket;
	this->conexionCliente = cliente;
	structPointer = &this->credencial;
	bytes = sizeof(credencial_t);
}

void EscuchadorCredenciales::casoError(int resultado){
	Log::getInstance()->huboUnErrorSDL("Hubo un error al recibir la informacion de las credenciales del cliente: " + this->conexionCliente->obtenerIP() + ", se cierra el socket", to_string(errno));
	throw runtime_error("ErrorAlRecibirCredenciales");
}

void EscuchadorCredenciales::casoSocketCerrado(){
	Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion de las credenciales del cliente: "+ this->conexionCliente->obtenerIP() +", se cierra el socket");
	throw runtime_error("ErrorAlRecibirCredenciales");
}

void EscuchadorCredenciales::casoExitoso(){
	string nombre;
	string contrasenia;

	nombre = string(credencial.nombre);
	contrasenia = string(credencial.contrasenia);

	Log::getInstance()->mostrarMensajeDeInfo("Se recibieron las credenciales:" + nombre + " | " +contrasenia +" del cliente: " + conexionCliente->obtenerIP());

	conexionCliente->recibirCredencial(nombre, contrasenia);
}

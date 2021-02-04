#include "EscuchadorCredenciales.hpp"

EscuchadorCredenciales::EscuchadorCredenciales(int socket, ConexionCliente* cliente){
	this->socket = socket;
	this->conexionCliente = cliente;
	structPointer = &this->credencial;
	bytes = sizeof(credencial_t);
}

void EscuchadorCredenciales::casoError(int resultado){
	Log::getInstance()->huboUnErrorSDL("Hubo un error al recibir la informacion de las credenciales del cliente: " + this->conexionCliente->obtenerIP() + ", se cierra el socket", std::to_string(errno));
	throw std::runtime_error("ErrorAlRecibirCredenciales");
}

void EscuchadorCredenciales::casoSocketCerrado(){
	Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion de las credenciales del cliente: "+ this->conexionCliente->obtenerIP() +", se cierra el socket");
	throw std::runtime_error("ErrorAlRecibirCredenciales");
}

void EscuchadorCredenciales::casoExitoso(){
    std::string nombre;
    std::string contrasenia;

	nombre = std::string(credencial.nombre);
	contrasenia = std::string(credencial.contrasenia);

	Log::getInstance()->mostrarMensajeDeInfo("Se recibieron las credenciales: (" + nombre + ";" +contrasenia +") del cliente: " + conexionCliente->obtenerIP());

	conexionCliente->recibirCredencial(nombre, contrasenia);
}

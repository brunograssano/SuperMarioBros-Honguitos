#include "EscuchadorCredenciales.hpp"

EscuchadorCredenciales::EscuchadorCredenciales(int socket, ConexionCliente* cliente){
	this->socket = socket;
	this->conexionCliente = cliente;
	structPointer = &this->credencial;
	bytes = sizeof(credencial_t);
}

void EscuchadorCredenciales::casoError(int resultado){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	Log::getInstance()->huboUnErrorSDL("Hubo un error al recibir la informacion de las credenciales del cliente: " + this->conexionCliente->obtenerIP() + ", se cierra el socket", to_string(errno));
	pthread_mutex_unlock(&mutex);
	throw runtime_error("ErrorAlRecibirCredenciales");
}

void EscuchadorCredenciales::casoSocketCerrado(){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion de las credenciales del cliente: "+ this->conexionCliente->obtenerIP() +", se cierra el socket");
	pthread_mutex_unlock(&mutex);
	throw runtime_error("ErrorAlRecibirCredenciales");
}

void EscuchadorCredenciales::casoExitoso(){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	string nombre;
	string contrasenia;

	nombre = string(credencial.nombre);
	contrasenia = string(credencial.contrasenia);

	pthread_mutex_lock(&mutex);
	Log::getInstance()->mostrarMensajeDeInfo("Se recibieron las credenciales:" + nombre + " | " +contrasenia +" del cliente: " + conexionCliente->obtenerIP());
	pthread_mutex_unlock(&mutex);

	conexionCliente->recibirCredencial(nombre, contrasenia);
}

EscuchadorCredenciales::~EscuchadorCredenciales(){

}

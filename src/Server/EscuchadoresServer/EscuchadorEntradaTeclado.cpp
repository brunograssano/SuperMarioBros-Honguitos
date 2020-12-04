#include "EscuchadorEntradaTeclado.hpp"

EscuchadorEntradaTeclado::EscuchadorEntradaTeclado(int socket, int idJugador, Servidor* servidor){
	this->idJugador = idJugador;
	this->socket = socket;
	this->servidor = servidor;
	structPointer = &this->entradaUsuario;
	bytes = sizeof(entrada_usuario_t);
}

void EscuchadorEntradaTeclado::casoError(int resultado){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	Log::getInstance()->huboUnErrorSDL("Hubo un error al recibir la informacion de entradas de usuario, se cierra el socket", to_string(errno));
	pthread_mutex_unlock(&mutex);
	throw runtime_error("ErrorAlRecibirEntradaTeclado");
}
void EscuchadorEntradaTeclado::casoSocketCerrado(){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion de entrada de teclado. Se cierra el socket");
	pthread_mutex_unlock(&mutex);
	throw runtime_error("ErrorAlRecibirEntradaTeclado");
}
void EscuchadorEntradaTeclado::casoExitoso(){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	entrada_usuario_id_t entradaUsuarioId;
	entradaUsuarioId.entradas = entradaUsuario;
	entradaUsuarioId.id = idJugador;
	pthread_mutex_lock(&mutex);
	servidor->encolarEntradaUsuario(entradaUsuarioId);
	pthread_mutex_unlock(&mutex);
}

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
	Log::getInstance()->huboUnErrorSDL("Hubo un error al recibir la informacion de entradas de usuario del jugador: "+ to_string(this->idJugador)+ ", se cierra el socket", to_string(errno));
	pthread_mutex_unlock(&mutex);
	throw runtime_error("ErrorAlRecibirEntradaTeclado");
}
void EscuchadorEntradaTeclado::casoSocketCerrado(){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion de entrada de teclado del jugador: "+ to_string(this->idJugador)+ ". Se cierra el socket");
	pthread_mutex_unlock(&mutex);
	throw runtime_error("ErrorAlRecibirEntradaTeclado");
}
void EscuchadorEntradaTeclado::casoExitoso(){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	entrada_usuario_id_t entradaUsuarioId;
	entradaUsuarioId.entradas = entradaUsuario;
	entradaUsuarioId.id = idJugador;

	bool esIdValido = false;

	for(auto const& parIdNombre :servidor->obtenerMapaJugadores()){
		if(entradaUsuarioId.id == parIdNombre.first){
			esIdValido = true;
		}
	}

	if(esIdValido){
		pthread_mutex_lock(&mutex);
		servidor->encolarEntradaUsuario(entradaUsuarioId);
		pthread_mutex_unlock(&mutex);
	}else{
		Log::getInstance()->mostrarMensajeDeInfo("El ID proveniente del cliente no es valido, se ignora la entrada del teclado");
	}
}

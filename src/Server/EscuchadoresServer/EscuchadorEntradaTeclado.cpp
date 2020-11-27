
#include "EscuchadorEntradaTeclado.hpp"


EscuchadorEntradaTeclado::EscuchadorEntradaTeclado(int socket, int idJugador, Servidor* servidor){
	this->idJugador = idJugador;
	this->socket = socket;
	this->servidor = servidor;
}

void EscuchadorEntradaTeclado::escuchar(){

	entrada_usuario_t entradaUsuario;
	entrada_usuario_id_t entradaUsuarioId;
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	int resultado = recv(socket, &entradaUsuario, sizeof(entrada_usuario_t), MSG_WAITALL);

	if(resultado<0){
		pthread_mutex_lock(&mutex);
		Log::getInstance()->huboUnErrorSDL("Hubo un error al recibir la informacion de entradas de usuario, se cierra el socket", to_string(errno));
		pthread_mutex_unlock(&mutex);
		throw runtime_error("ErrorAlRecibirEntradaTeclado");
	}else if(resultado == 0){
		pthread_mutex_lock(&mutex);
		Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion, se cierra el socket");
		pthread_mutex_unlock(&mutex);
		throw runtime_error("ErrorAlRecibirEntradaTeclado");
	}

	entradaUsuarioId.entradas = entradaUsuario;
	entradaUsuarioId.id = idJugador;
	servidor->encolarEntradaUsuario(entradaUsuarioId);


}

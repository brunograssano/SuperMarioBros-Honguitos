#include "EscuchadorEntradaTeclado.hpp"

EscuchadorEntradaTeclado::EscuchadorEntradaTeclado(Socket* socket, int idJugador, Servidor* servidor){
	this->idJugador = idJugador;
	this->socket = socket;
	this->servidor = servidor;
	structPointer = &this->entradaUsuario;
	bytes = sizeof(entrada_usuario_t);
}

void EscuchadorEntradaTeclado::casoError(int resultado){
	Log::getInstance()->huboUnErrorSDL("Hubo un error al recibir la informacion de entradas de usuario del jugador: "
	+ std::to_string(this->idJugador)+ ", se cierra el socket", std::to_string(errno));
	throw std::runtime_error("ErrorAlRecibirEntradaTeclado");
}
void EscuchadorEntradaTeclado::casoSocketCerrado(){
	Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion de entrada de teclado del jugador: "
	+ std::to_string(this->idJugador)+ ". Se cierra el socket");
	throw std::runtime_error("ErrorAlRecibirEntradaTeclado");
}
void EscuchadorEntradaTeclado::casoExitoso(){
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
		servidor->encolarEntradaUsuario(entradaUsuarioId);
	}else{
		Log::getInstance()->mostrarMensajeDeInfo("El ID proveniente del cliente no es valido, se ignora la entrada del teclado");
	}
}

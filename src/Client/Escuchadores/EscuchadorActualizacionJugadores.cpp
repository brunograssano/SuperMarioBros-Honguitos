#include "EscuchadorActualizacionJugadores.hpp"

EscuchadorActualizacionJugadores::EscuchadorActualizacionJugadores(int socket, Cliente* cliente){
	this->socket = socket;
	this->cliente = cliente;
	structPointer = &this->actualizacion;
	bytes = sizeof(actualizacion_cantidad_jugadores_t);
	this->error = string("");
}

void EscuchadorActualizacionJugadores::casoError(int resultado){
	Log::getInstance()->huboUnErrorSDL("Hubo un error al recibir la informacion de actualizacion de jugadores, se cierra el socket", to_string(errno));
	throw runtime_error("ErrorAlEscucharActualizacionJugadores");
}
void EscuchadorActualizacionJugadores::casoSocketCerrado(){
	Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion de actualizacion de jugadores, se cierra el socket");
	throw runtime_error("ErrorAlEscucharActualizacionJugadores");
}

bool EscuchadorActualizacionJugadores::idsValidas(par_id_nombre_t pares_id_nombre[MAX_JUGADORES], int tope){
	for(int i = 0; i < tope; i++){
		if(pares_id_nombre[i].id >= 4){
			return false;
		}
	}
	return true;
}

bool EscuchadorActualizacionJugadores::recibioMensajeValido(){
	bool ocurrioError = false;
	if(actualizacion.cantidadJugadoresActivos > actualizacion.cantidadMaximaDeJugadores){
		error = string("La cantidad de usuarios activos supera a la cantidad maxima de jugadores.");
		ocurrioError = true;
	}else if(actualizacion.cantidadMaximaDeJugadores == 0){
		error = string("La cantidad maxima de usuarios es 0.");
		ocurrioError = true;
	}else if(actualizacion.tope > actualizacion.cantidadMaximaDeJugadores){
		error = string("El tope es mayor a la cantidad maxima de jugadores.");
		ocurrioError = true;
	}else if(!idsValidas(actualizacion.pares_id_nombre, actualizacion.tope)){
		error = string("Una id es mayor a 4.");
		ocurrioError = true;
	}
	return !ocurrioError;
}

void EscuchadorActualizacionJugadores::casoExitoso(){
	if(!recibioMensajeValido()){
		Log::getInstance()->huboUnError("Se desecho el mensaje recibido del servidor debido que: " + error);
		return;
	}else{
		this->cliente->recibirInformacionActualizacion(actualizacion);
	}
}

EscuchadorActualizacionJugadores::~EscuchadorActualizacionJugadores(){

}

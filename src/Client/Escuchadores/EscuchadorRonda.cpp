#include "EscuchadorRonda.hpp"
#include "src/Utils/log/Log.hpp"
#include "src/Utils/Constantes.hpp"

EscuchadorRonda::EscuchadorRonda(int socket, Cliente* cliente){
	this->socket = socket;
	this->cliente = cliente;
	structPointer = &this->info_ronda;
	bytes = sizeof(info_ronda_t);
	error = std::string("");
}

void EscuchadorRonda::casoError(int resultado){
	Log::getInstance()->huboUnErrorSDL("Hubo un error al escuchar informacion de la ronda, se cierra el socket", std::to_string(errno));
	throw std::runtime_error("ErrorAlEscucharInformacionDeLaRonda");
}

void EscuchadorRonda::casoSocketCerrado(){
	Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion de la ronda, se cierra el socket");
	throw std::runtime_error("ErrorAlEscucharInformacionDeLaRonda");
}


bool EscuchadorRonda::bloquesValidos(entidad_t bloques[MAX_SORPRESAS], int tope){
	for(int i = 0; i < tope; i++){
		if(bloques[i].recorteX > ESTADOS_BLOQUE ||
		   bloques[i].recorteY > COLORES_BLOQUES_POSIBLES){
			return false;
		}
	}
	return true;
}

bool EscuchadorRonda::monedasValidas(entidad_t monedas[MAX_MONEDAS], int tope){
	for(int i = 0; i < tope; i++){
		if(monedas[i].recorteX > ESTADOS_MONEDA){
			return false;
		}
	}
	return true;
}

bool EscuchadorRonda::enemigosValidos(entidad_t enemigos[MAX_ENEMIGOS], int tope){
	for(int i = 0; i < tope; i++){
        entidad_t enemigo = enemigos[i];
		if((enemigo.tipo != TIPO_GOOMBA && enemigo.tipo != TIPO_KOOPA)||
			((enemigo.tipo == TIPO_GOOMBA && (enemigo.recorteX > ESTADOS_GOOMBA || enemigo.recorteY > COLORES_GOOMBA_POSIBLES)) ||
			(enemigo.tipo == TIPO_KOOPA && (enemigo.recorteX > ESTADOS_KOOPA || enemigo.recorteY > COLORES_KOOPA_POSIBLES)))){
			return false;
		}
	}
	return true;
}

bool EscuchadorRonda::recibioMensajeValido(){
	bool ocurrioError = false;

	if(!bloquesValidos(info_ronda.bloques, info_ronda.topeBloques)){
		error = std::string("El vector de bloques posee al menos un bloque invalido.");
		ocurrioError = true;
	}else if(!monedasValidas(info_ronda.monedas, info_ronda.topeMonedas)){
		error = std::string("El vector de monedas posee al menos un bloque invalido.");
		ocurrioError = true;
	}else if(!enemigosValidos(info_ronda.enemigos, info_ronda.topeEnemigos)){
		error = std::string("El vector de enemigos posee al menos un enemigo invalido.");
		ocurrioError = true;
	}
	return !ocurrioError;
}

void EscuchadorRonda::casoExitoso(){
	if(!recibioMensajeValido()){
		Log::getInstance()->huboUnError("Se desecho el mensaje recibido del servidor debido que: " + error);
		return;
	}else{
		cliente->recibirInformacionRonda(info_ronda);
	}
}
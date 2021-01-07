#include "EscuchadorRonda.hpp"
EscuchadorRonda::EscuchadorRonda(int socket, Cliente* cliente){
	this->socket = socket;
	this->cliente = cliente;
	structPointer = &this->info_ronda;
	bytes = sizeof(info_ronda_t);
	error = string("");
}

void EscuchadorRonda::casoError(int resultado){
	Log::getInstance()->huboUnErrorSDL("Hubo un error al escuchar informacion de la ronda, se cierra el socket", to_string(errno));
	throw runtime_error("ErrorAlEscucharInformacionDeLaRonda");
}

void EscuchadorRonda::casoSocketCerrado(){
	Log::getInstance()->mostrarMensajeDeInfo("No se recibio mas informacion de la ronda, se cierra el socket");
	throw runtime_error("ErrorAlEscucharInformacionDeLaRonda");
}


bool EscuchadorRonda::bloquesValidos(bloque_t bloques[MAX_BLOQUES], int tope){
	for(int i = 0; i < tope; i++){
		if(bloques[i].numeroRecorteX > ESTADOS_BLOQUE ||
		   bloques[i].numeroRecorteY > COLORES_BLOQUES_POSIBLES){
			return false;
		}
	}
	return true;
}

bool EscuchadorRonda::monedasValidas(moneda_t monedas[MAX_MONEDAS], int tope){
	for(int i = 0; i < tope; i++){
		if(monedas[i].numeroRecorte > ESTADOS_MONEDA){
			return false;
		}
	}
	return true;
}

bool EscuchadorRonda::enemigosValidos(enemigo_t enemigos[MAX_ENEMIGOS], int tope){
	for(int i = 0; i < tope; i++){
		enemigo_t enemigo = enemigos[i];
		if((enemigo.tipoEnemigo != TIPO_GOOMBA && enemigo.tipoEnemigo != TIPO_KOOPA)||
			((enemigo.tipoEnemigo == TIPO_GOOMBA && (enemigo.numeroRecorteX > ESTADOS_GOOMBA || enemigo.numeroRecorteY > COLORES_GOOMBA_POSIBLES)) ||
			(enemigo.tipoEnemigo == TIPO_KOOPA && (enemigo.numeroRecorteX > ESTADOS_KOOPA || enemigo.numeroRecorteY > COLORES_KOOPA_POSIBLES)))){
			return false;
		}
	}
	return true;
}

bool EscuchadorRonda::recibioMensajeValido(){
	bool ocurrioError = false;

	if(info_ronda.mundo < 0){
		error = string("El numero del mundo es menor que 0.");
		ocurrioError = true;
	}else if(!bloquesValidos(info_ronda.bloques, info_ronda.topeBloques)){
		error = string("El vector de bloques posee al menos un bloque invalido.");
		ocurrioError = true;
	}else if(!monedasValidas(info_ronda.monedas, info_ronda.topeMonedas)){
		error = string("El vector de monedas posee al menos un bloque invalido.");
		ocurrioError = true;
	}else if(!enemigosValidos(info_ronda.enemigos, info_ronda.topeEnemigos)){
		error = string("El vector de enemigos posee al menos un enemigo invalido.");
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

EscuchadorRonda::~EscuchadorRonda()= default;

#ifndef SRC_LOG_H_
#define SRC_LOG_H_

#include "TipoLog.h"

class Log{

private:

	TipoLog* tipoLog;

public:

	Log(TipoLog* tipoLog){
		this->tipoLog = tipoLog;
	}

	//DEBUG//
	void mostrarPosicionMario(int coordenadaX, int coordenadaY){
		this->tipoLog->mostrarPosicionMario(coordenadaX, coordenadaY);
	}

	//INFO//
	void seCargaUnaTexturaDesde(string rutaTextura){
		this->tipoLog->seCargaUnaTexturaDesde(rutaTextura);
	}

	//ERRORES//
	void huboUnErrorAlInicializar(){
		this->tipoLog->huboUnErrorAlInicializar();
	}

	void huboUnErrorEnLaCargaDeLaTextura(string rutaTextura){
		this->huboUnErrorEnLaCargaDeLaTextura(rutaTextura);
	}

};



#endif /* SRC_LOG_H_ */

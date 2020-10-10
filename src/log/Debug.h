
#ifndef SRC_LOG_DEBUG_H_
#define SRC_LOG_DEBUG_H_

#include "TipoLog.h"

class Debug : public TipoLog{

	//INFO//
	virtual void seCargaUnaTexturaDesde(string rutaTextura) override {	}

	//ERRORES//
	virtual void huboUnErrorAlInicializar() override {	}
	virtual void huboUnErrorEnLaCargaDeLaTextura(string rutaTextura) override {	}

};


#endif /* SRC_LOG_DEBUG_H_ */

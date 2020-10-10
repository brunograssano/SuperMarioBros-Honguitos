

#ifndef SRC_LOG_INFO_H_
#define SRC_LOG_INFO_H_

#include "TipoLog.h"

class Info : public TipoLog{

	//ERRORES//
	virtual void huboUnErrorAlInicializar() override {	}
	virtual void huboUnErrorEnLaCargaDeLaTextura(string rutaTextura) override {	}

};


#endif /* SRC_LOG_INFO_H_ */

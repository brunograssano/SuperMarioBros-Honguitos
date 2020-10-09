
#ifndef SRC_MODELO_MONEDA_H_
#define SRC_MODELO_MONEDA_H_

#include "Posicion.h"

class Moneda{

public:
	Moneda(int coordenadaX, int coordenadaY){
		this->posicion = new PosicionFija(coordenadaX, coordenadaY);
	}

	~Moneda(){
		delete this->posicion;
	}

private:
	Posicion* posicion;
};


#endif /* SRC_MODELO_MONEDA_H_ */

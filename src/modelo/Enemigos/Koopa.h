#ifndef SRC_MODELO_ENEMIGOS_KOOPA_H_
#define SRC_MODELO_ENEMIGOS_KOOPA_H_

#include "Enemigo.h"

class Koopa : public Enemigo{

public:

	Koopa(int coordenadaX, int coordenadaY){
		this->posicionActual = new PosicionMovil(coordenadaX, coordenadaY);
	}

	~Koopa(){
		delete this->posicionActual;
	}

};

#endif /* SRC_MODELO_ENEMIGOS_KOOPA_H_ */

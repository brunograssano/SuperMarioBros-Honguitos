
#ifndef SRC_MODELO_ENEMIGOS_GOOMBA_H_
#define SRC_MODELO_ENEMIGOS_GOOMBA_H_

#include "Enemigo.h"

class Goomba : public Enemigo{

public:

	Goomba(int coordenadaX, int coordenadaY){
		this->posicionActual = new PosicionMovil(coordenadaX, coordenadaY);
	}

	~Goomba(){
		delete this->posicionActual;
	}

};

#endif /* SRC_MODELO_ENEMIGOS_GOOMBA_H_ */

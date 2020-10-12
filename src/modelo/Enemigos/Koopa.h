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

		void actualizarPosicion()override{
			this->posicionActual->moverHorizontal(velocidadX);
		}

	private:
		float velocidadX = 0.05;
};

#endif /* SRC_MODELO_ENEMIGOS_KOOPA_H_ */

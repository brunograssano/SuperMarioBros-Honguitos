
#ifndef SRC_MODELO_ENEMIGOS_GOOMBA_H_
#define SRC_MODELO_ENEMIGOS_GOOMBA_H_

#include "Enemigo.h"

class Goomba : public Enemigo{

	public:

		Goomba(int coordenadaX, int coordenadaY){
			this->posicionActual = new PosicionMovil(coordenadaX, coordenadaY);
		}



		void actualizarPosicion()override{
			this->posicionActual->moverHorizontal(velocidadX);
		}

		~Goomba(){
			delete this->posicionActual;
		}
	private:
		float velocidadX = 0.05;

};

#endif /* SRC_MODELO_ENEMIGOS_GOOMBA_H_ */

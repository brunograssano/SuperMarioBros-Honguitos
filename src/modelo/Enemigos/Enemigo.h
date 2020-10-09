#ifndef SRC_MODELO_ENEMIGOS_ENEMIGO_H_
#define SRC_MODELO_ENEMIGOS_ENEMIGO_H_

#include "Posicion.h"
#include "../Movimiento.h"

class Enemigo{

	public:
		void mover(Movimiento* unMovimiento){
			unMovimiento->mover(posicionActual);
		}

		int obtenerPosicionX(){
			return posicionActual->obtenerPosX();
		}

		int obtenerPosicionY(){
			return posicionActual->obtenerPosY();
		}

		virtual ~Enemigo();

	protected:
		PosicionMovil* posicionActual;

};


#endif /* SRC_MODELO_ENEMIGOS_ENEMIGO_H_ */

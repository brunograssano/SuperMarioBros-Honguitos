#ifndef SRC_MODELO_ENEMIGOS_ENEMIGO_H_
#define SRC_MODELO_ENEMIGOS_ENEMIGO_H_

#include "../Posicion.h"

class Enemigo{

	public:

		int obtenerPosicionX(){
			return posicionActual->obtenerPosX();
		}

		int obtenerPosicionY(){
			return posicionActual->obtenerPosY();
		}


		virtual void actualizarPosicion(){};

		virtual ~Enemigo(){};

	protected:
		PosicionMovil* posicionActual;

};


#endif /* SRC_MODELO_ENEMIGOS_ENEMIGO_H_ */

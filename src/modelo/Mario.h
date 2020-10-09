#ifndef SRC_MODELO_MARIO_H_
#define SRC_MODELO_MARIO_H_

#include "Movimientos/Movimiento.h"

class Mario{

	public:

		Mario();
		void mover(Movimiento* unMovimiento);
		int obtenerPosicion();
		~Mario();

	private:

		int posicionX;
		int puntos;


};


#endif

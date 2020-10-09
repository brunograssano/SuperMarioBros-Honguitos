#ifndef SRC_MODELO_MARIO_H_
#define SRC_MODELO_MARIO_H_

#include "Movimientos/Movimiento.h"

class Mario{

	public:

		Mario();
		void mover(Movimiento* unMovimiento);
		int obtenerPosicionX();
		int obtenerPosicionY();
		int obtenerPuntos();
		void agregarPuntos(int unosPuntos);
		int obtenerMonedas();
		void agregarMoneda();

		~Mario();

	private:

		PosicionMovil* posicion;
		int puntos;
		int cantidadMonedas;


};


#endif

#ifndef SRC_MODELO_MARIO_H_
#define SRC_MODELO_MARIO_H_

#include "../modelo/Posicion.h"
#include "../modelo/movimiento/MovimientoMario.h"

class Mario{

	public:

		Mario();
		int obtenerPosicionX();
		int obtenerPosicionY();
		int obtenerPuntos();
		void agregarPuntos(int unosPuntos);
		int obtenerMonedas();
		void agregarMoneda();

		void moveraArriba();
		void moveraAbajo();
		void aceleraraIzquierda();
		void aceleraraDerecha();
		void saltar();

		void actualizarPosicion();

		~Mario();

	private:
		PosicionMovil* posicion;
		int puntos;
		int cantidadMonedas;
		MovimientoMario* movimiento;
};


#endif

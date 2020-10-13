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

		void moveraArriba();		//TODO Eliminar este método. Ojo con los test.
		void moveraAbajo();			//TODO Eliminar este método. Ojo con los test.
		void aceleraraIzquierda();
		void aceleraraDerecha();
		void saltar();

		void actualizarPosicion();

		~Mario();

	private:
		PosicionMovil* posicion;
		MovimientoMario* movimiento;
		int puntos;
		int cantidadMonedas;
		bool estaSaltando;
};


#endif

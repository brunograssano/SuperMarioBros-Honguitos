#ifndef SRC_MODELO_MARIO_H_
#define SRC_MODELO_MARIO_H_

#include "../modelo/Posicion.h"
#include "../modelo/movimiento/MovimientoMario.h"

class Mario{

	public:

		Mario();
		int obtenerPuntos();
		void agregarPuntos(int unosPuntos);
		int obtenerMonedas();
		void agregarMoneda();

		int obtenerPosicionX();
		int obtenerPosicionY();
		void aceleraraIzquierda();
		void aceleraraDerecha();
		void saltar();
		bool estaQuietoX();
		bool estaEnElPiso();
		void actualizarPosicion();
		
		void actualizarLimiteDeMovimiento(int limiteActual);

		~Mario();

	private:
		PosicionMovil* posicion;
		MovimientoMario* movimiento;
		int puntos;
		int cantidadMonedas;
};


#endif

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

		void moveraArriba();
		void moveraAbajo();
		void aceleraraIzquierda();
		void aceleraraDerecha();

		void actualizarPosicion();

		~Mario();

	private:
		void actualizarVelocidad();
		void aplicarCoeficienteDeRozamiento();
		PosicionMovil* posicion;
		float velocidadX = 0;
		float aceleracionX = 0;
		int puntos;
		int cantidadMonedas;

};


#endif

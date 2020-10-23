#ifndef SRC_MODELO_MOVIMIENTO_MOVIMIENTOHORIZONTALMARIO_H_
#define SRC_MODELO_MOVIMIENTO_MOVIMIENTOHORIZONTALMARIO_H_

#include "../Posicion.h"

class MovimientoHorizontalMario{

	public:
		MovimientoHorizontalMario();
		void aceleraraDerecha();
		void aceleraraIzquierda();
		void mover(PosicionMovil* posicion);
		bool estaQuieto();
		void actualizarLimiteTerrenoIzq(int limiteActual) {
			this->limite_terreno_izq_actual = limiteActual;
		}
	private:
		void actualizarVelocidad();
		void aplicarCoeficienteDeRozamiento();
		float aceleracionX;
		float velocidadX;
		int limite_terreno_izq_actual;
};

#endif /* SRC_MODELO_MOVIMIENTO_MOVIMIENTOHORIZONTALMARIO_H_ */

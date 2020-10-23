#ifndef SRC_MODELO_MOVIMIENTO_MOVIMIENTOHORIZONTAL_H_
#define SRC_MODELO_MOVIMIENTO_MOVIMIENTOHORIZONTAL_H_

#include "../Posicion.h"
#include "Terreno/Terreno.h"

class MovimientoHorizontal{

	public:
		MovimientoHorizontal(float maximaVelocidad, float aceleracion);
		void aceleraraDerecha(Terreno* terreno);
		void aceleraraIzquierda(Terreno* terreno);
		void mover(PosicionMovil* posicion, Terreno* terreno);
		bool estaQuieto();
		void actualizarLimiteTerrenoIzq(int limiteActual) {
			this->limite_terreno_izq_actual = limiteActual;
		}
	private:
		void aplicarCoeficienteDeRozamiento();
		float velocidadX;
		float maximaVelocidadX;
		float aceleracionX;
		int limite_terreno_izq_actual;
};

#endif /* SRC_MODELO_MOVIMIENTO_MOVIMIENTOHORIZONTAL_H_ */

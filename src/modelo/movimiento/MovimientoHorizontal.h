#ifndef SRC_MODELO_MOVIMIENTO_MOVIMIENTOHORIZONTAL_H_
#define SRC_MODELO_MOVIMIENTO_MOVIMIENTOHORIZONTAL_H_

#include "../Posicion.h"
#include "../Terreno/Terreno.h"

class MovimientoHorizontal{

	public:
		MovimientoHorizontal(float maximaVelocidad, float aceleracion);
		void aceleraraDerecha(Terreno* terreno);
		void aceleraraIzquierda(Terreno* terreno);
		void mover(PosicionMovil* posicion, Terreno* terreno);
		bool estaQuieto();
	private:
		void aplicarCoeficienteDeRozamiento();
		float velocidadX;
		float maximaVelocidadX;
		float aceleracionX;
};

#endif /* SRC_MODELO_MOVIMIENTO_MOVIMIENTOHORIZONTAL_H_ */

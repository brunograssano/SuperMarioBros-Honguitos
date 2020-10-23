#ifndef SRC_MODELO_MOVIMIENTO_MOVIMIENTOMARIO_H_
#define SRC_MODELO_MOVIMIENTO_MOVIMIENTOMARIO_H_

#include "../Posicion.h"
#include "MovimientoHorizontalMario.h"
class MovimientoMario{

	public:
		MovimientoMario();
		void aceleraraDerecha();
		void aceleraraIzquierda();
		void saltar();
		void mover(PosicionMovil* posicion);
		void setVelocidadY(int velocidad){
			this->velocidadY = velocidad;
		}
		bool estaQuieto();
	
		void actualizarLimiteTerrenoIzq(int limiteActual) {
		    this->movimientoX->actualizarLimiteTerrenoIzq(limiteActual);
		}
	private:
		void aplicarGravedad();
		float aceleracionY;
		float velocidadY;
		MovimientoHorizontalMario* movimientoX;
};


#endif /* SRC_MODELO_MOVIMIENTO_MOVIMIENTOMARIO_H_ */

#ifndef SRC_MODELO_MOVIMIENTO_MOVIMIENTOMARIO_H_
#define SRC_MODELO_MOVIMIENTO_MOVIMIENTOMARIO_H_

#include "../Posicion.h"
#include "MovimientoHorizontalMario.h"
#include "MovimientoVerticalMario.h"
class MovimientoMario{

	public:
		MovimientoMario();
		void aceleraraDerecha();
		void aceleraraIzquierda();
		bool estaQuieto();
		void actualizarLimiteTerrenoIzq(int limiteActual) {
		    this->movimientoX->actualizarLimiteTerrenoIzq(limiteActual);
		}
		void saltar();
		void setVelocidadY(int velocidad){
			this->movimientoY->setVelocidadY(velocidad);
		}
		void mover(PosicionMovil* posicion);

	private:
		MovimientoHorizontalMario* movimientoX;
		MovimientoVerticalMario* movimientoY;
};


#endif /* SRC_MODELO_MOVIMIENTO_MOVIMIENTOMARIO_H_ */

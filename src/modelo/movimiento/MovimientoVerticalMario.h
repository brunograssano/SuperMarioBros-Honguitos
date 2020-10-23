#ifndef SRC_MODELO_MOVIMIENTO_MOVIMIENTOVERTICALMARIO_H_
#define SRC_MODELO_MOVIMIENTO_MOVIMIENTOVERTICALMARIO_H_

#include "../Posicion.h"

class MovimientoVerticalMario{

	public:
		MovimientoVerticalMario();
		void saltar();
		void mover(PosicionMovil* posicion);
		void setVelocidadY(int velocidad){
			this->velocidadY = velocidad;
		}

	private:
		void aplicarGravedad();
		float aceleracionY;
		float velocidadY;
};



#endif /* SRC_MODELO_MOVIMIENTO_MOVIMIENTOVERTICALMARIO_H_ */

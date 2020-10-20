#ifndef SRC_MODELO_MOVIMIENTO_MOVIMIENTOMARIO_H_
#define SRC_MODELO_MOVIMIENTO_MOVIMIENTOMARIO_H_

#include "../Posicion.h"

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
	private:
		void actualizarVelocidad();
		void aplicarGravedad();
		void aplicarCoeficienteDeRozamiento();
		float aceleracionX;
		float aceleracionY;
		float velocidadX;
		float velocidadY;
};


#endif /* SRC_MODELO_MOVIMIENTO_MOVIMIENTOMARIO_H_ */

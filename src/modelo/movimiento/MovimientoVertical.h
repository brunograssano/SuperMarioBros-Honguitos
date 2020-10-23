#ifndef SRC_MODELO_MOVIMIENTO_MOVIMIENTOVERTICAL_H_
#define SRC_MODELO_MOVIMIENTO_MOVIMIENTOVERTICAL_H_

#include "../Posicion.h"
#include "Terreno/Terreno.h"

class MovimientoVertical{

	public:
		MovimientoVertical(float fuerza);
		void saltar(Terreno* terreno);
		void mover(PosicionMovil* posicion);
		void setVelocidadY(int velocidad){
			this->velocidadY = velocidad;
		}

	private:
		void aplicarGravedad();
		float velocidadY;
		float fuerza;
};



#endif /* SRC_MODELO_MOVIMIENTO_MOVIMIENTOVERTICAL_H_ */

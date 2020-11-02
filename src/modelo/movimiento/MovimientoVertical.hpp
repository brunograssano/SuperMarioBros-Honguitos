#ifndef SRC_MODELO_MOVIMIENTO_MOVIMIENTOVERTICAL_HPP_
#define SRC_MODELO_MOVIMIENTO_MOVIMIENTOVERTICAL_HPP_

#include "../Posicion.hpp"
#include "../Terreno/Terreno.hpp"

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



#endif /* SRC_MODELO_MOVIMIENTO_MOVIMIENTOVERTICAL_HPP_ */

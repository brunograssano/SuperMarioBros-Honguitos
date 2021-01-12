#ifndef SRC_SERVER_MODELO_MOVIMIENTO_MOVIMIENTOVERTICAL_HPP_
#define SRC_SERVER_MODELO_MOVIMIENTO_MOVIMIENTOVERTICAL_HPP_

#include "../PosicionMovil.hpp"
#include "../Terreno/Terreno.hpp"

class MovimientoVertical{

	public:
		explicit MovimientoVertical(float fuerza);
		void saltar(Terreno* terreno);
		void mover(PosicionMovil* posicion);
		void setVelocidadY(int velocidad){
			this->velocidadY = (float)velocidad;
		}


private:
		void aplicarGravedad();
		float velocidadY;
		float fuerza;
};



#endif /* SRC_SERVER_MODELO_MOVIMIENTO_MOVIMIENTOVERTICAL_HPP_ */

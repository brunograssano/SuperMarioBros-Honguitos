#ifndef SRC_SERVER_MODELO_MOVIMIENTO_MOVIMIENTOVERTICAL_HPP_
#define SRC_SERVER_MODELO_MOVIMIENTO_MOVIMIENTOVERTICAL_HPP_

#include "src/Server/Modelo/Juego/Posiciones/PosicionMovil.hpp"
#include "src/Server/Modelo/Juego/Terrenos/Terreno.hpp"

class MovimientoVertical{

	public:
		explicit MovimientoVertical(float fuerza);
		void saltar(Terreno* terreno);
		void mover(PosicionMovil* posicion);
		void setVelocidadY(int velocidad);

    private:
		void aplicarGravedad();
		float velocidadY;
		float fuerza;
};



#endif /* SRC_SERVER_MODELO_MOVIMIENTO_MOVIMIENTOVERTICAL_HPP_ */

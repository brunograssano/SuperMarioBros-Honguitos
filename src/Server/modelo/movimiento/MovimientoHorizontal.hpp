#ifndef SRC_SERVER_MODELO_MOVIMIENTO_MOVIMIENTOHORIZONTAL_HPP_
#define SRC_SERVER_MODELO_MOVIMIENTO_MOVIMIENTOHORIZONTAL_HPP_

#include "../Posicion.hpp"
#include "../Terreno/Terreno.hpp"

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

#endif /* SRC_SERVER_MODELO_MOVIMIENTO_MOVIMIENTOHORIZONTAL_HPP_ */
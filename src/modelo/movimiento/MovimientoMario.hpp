#ifndef SRC_MODELO_MOVIMIENTO_MOVIMIENTOMARIO_HPP_
#define SRC_MODELO_MOVIMIENTO_MOVIMIENTOMARIO_HPP_

#include "../Posicion.hpp"
#include "../Terreno/Aire.hpp"
#include "../Terreno/Terreno.hpp"
#include "../Terreno/Tierra.hpp"
#include "MovimientoHorizontal.hpp"
#include "MovimientoVertical.hpp"

class MovimientoMario{
	public:
		MovimientoMario();
		~MovimientoMario();
		void aceleraraDerecha();
		void aceleraraIzquierda();
		bool estaQuieto();
		void saltar();
		void setVelocidadY(int velocidad){
			this->movimientoY->setVelocidadY(velocidad);
		}
		void mover(PosicionMovil* posicion);

	private:
		MovimientoHorizontal* movimientoX;
		MovimientoVertical* movimientoY;
		Terreno* terrenoActual;
};


#endif /* SRC_MODELO_MOVIMIENTO_MOVIMIENTOMARIO_HPP_ */

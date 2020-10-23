#ifndef SRC_MODELO_MOVIMIENTO_MOVIMIENTOMARIO_H_
#define SRC_MODELO_MOVIMIENTO_MOVIMIENTOMARIO_H_

#include "../Posicion.h"
#include "MovimientoHorizontal.h"
#include "MovimientoVertical.h"
#include "Terreno/Terreno.h"
#include "Terreno/Tierra.h"
#include "Terreno/Aire.h"

class MovimientoMario{
	public:
		MovimientoMario();
		~MovimientoMario();
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
		MovimientoHorizontal* movimientoX;
		MovimientoVertical* movimientoY;
		Terreno* terrenoActual;
};


#endif /* SRC_MODELO_MOVIMIENTO_MOVIMIENTOMARIO_H_ */

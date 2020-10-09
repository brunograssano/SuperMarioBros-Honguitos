#ifndef SRC_MODELO_MOVIMIENTOS_MOVIMIENTO_H_
#define SRC_MODELO_MOVIMIENTOS_MOVIMIENTO_H_

#include "../Posicion.h"

class Movimiento{
    public:
		virtual void mover(Posicion* posicionActual)=0;
		virtual ~Movimiento(){};

    protected:
		int movimiento;

};

class MovimientoDerecha : public Movimiento{
    public:
		MovimientoDerecha(int movimiento){
			this->movimiento = movimiento;
		}

        void mover(Posicion* posicionActual)override{
             posicionActual->moverHorizontal(this->movimiento);
        }

        ~MovimientoDerecha(){
        }

};

class MovimientoIzquierda : public Movimiento{
    public:
		MovimientoIzquierda(int movimiento){
			this->movimiento = movimiento;
		}

		void mover(Posicion* posicionActual)override{
			posicionActual->moverHorizontal(-1 * this->movimiento);
        }

        ~MovimientoIzquierda(){
        }

};

class MovimientoArriba : public Movimiento{
    public:
		MovimientoArriba(int movimiento){
			this->movimiento = movimiento;
		}

		void mover(Posicion* posicionActual)override{
			posicionActual->moverVertical(this->movimiento);
        }

        ~MovimientoArriba(){
        }

};

class MovimientoAbajo : public Movimiento{
    public:
		MovimientoAbajo(int movimiento){
			this->movimiento = movimiento;
		}

		void mover(Posicion* posicionActual)override{
			posicionActual->moverVertical(-1 * this->movimiento);
        }

        ~MovimientoAbajo(){
        }

};
#endif /* SRC_MODELO_MOVIMIENTOS_MOVIMIENTO_H_ */

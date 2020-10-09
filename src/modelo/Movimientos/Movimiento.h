
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


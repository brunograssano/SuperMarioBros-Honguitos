


class Movimiento{
    public:
		virtual int mover(int posicionActual)=0;
		virtual ~Movimiento(){};

};

class MovimientoDerecha : public Movimiento{
    public:
		MovimientoDerecha(int movimiento){
			this->movimiento = movimiento;
		}

        int mover(int posicionActual)override{
            return posicionActual + this->movimiento;
        }

        ~MovimientoDerecha(){
        }
    private:
        int movimiento;
};

class MovimientoIzquierda : public Movimiento{
    public:
		MovimientoIzquierda(int movimiento){
			this->movimiento = movimiento;
		}

        int mover(int posicionActual)override{
            return posicionActual - this->movimiento;
        }

        ~MovimientoIzquierda(){
        }
    private:
        int movimiento;
};


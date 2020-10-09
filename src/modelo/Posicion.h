#ifndef SRC_MODELO_POSICION_H_
#define SRC_MODELO_POSICION_H_


class Posicion{

	public:

		Posicion(int coordenadaX,int coordenadaY){
			this->posicionX=coordenadaX;
			this->posicionY=coordenadaY;
		};

		void moverHorizontal(int cantidadAMover){
			this->posicionX+=cantidadAMover;
		};

		void moverVertical(int cantidadAMover){
			this->posicionY+=cantidadAMover;
		};

		int obtenerPosX(){
			return this->posicionX;
		}

		int obtenerPosY(){
			return this->posicionY;
		}

		~Posicion(){};

	private:

		int posicionX;
		int posicionY;


};



#endif /* SRC_MODELO_POSICION_H_ */

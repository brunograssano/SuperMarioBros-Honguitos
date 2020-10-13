#ifndef SRC_MODELO_POSICION_H_
#define SRC_MODELO_POSICION_H_


class Posicion{

	public:

		int obtenerPosX(){
			return this->posicionX;
		}

		int obtenerPosY(){
			return this->posicionY;
		}

	protected:

		float posicionX;
		int posicionY;
		int minimoY;

};


class PosicionMovil : public Posicion{

	public:

		PosicionMovil(int coordenadaX,int coordenadaY, int minimoY){
			this->posicionX=coordenadaX;
			this->posicionY=coordenadaY;
			this->minimoY = minimoY;
		}

		PosicionMovil(int coordenadaX, int coordenadaY){
			this->posicionX=coordenadaX;
			this->posicionY=coordenadaY;
			this->minimoY = 2147483647;
		}

		void moverHorizontal(int cantidadAMover){
			this->posicionX+=(float)cantidadAMover;
		}

		void moverHorizontal(float cantidadAMover){
			this->posicionX+=cantidadAMover;
		}

		void moverVertical(int cantidadAMover){
			if(posicionY + cantidadAMover < minimoY){
				posicionY = minimoY;
			}else{
				this->posicionY+=cantidadAMover;
			}
		}

		~PosicionMovil(){}

};

class PosicionFija : public Posicion{

	public:

		PosicionFija(int coordenadaX,int coordenadaY){
			this->posicionX=coordenadaX;
			this->posicionY=coordenadaY;
		}

};

#endif /* SRC_MODELO_POSICION_H_ */

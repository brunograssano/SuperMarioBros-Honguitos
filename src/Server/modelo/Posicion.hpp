#ifndef SRC_SERVER_MODELO_POSICION_HPP_
#define SRC_SERVER_MODELO_POSICION_HPP_


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

		PosicionMovil(int coordenadaX,int coordenadaY, int minimoY, int minimoX, int maximoX){
			this->posicionX=coordenadaX;
			this->posicionY=coordenadaY;
			this->minimoY = minimoY;
			this->minimoX = minimoX;
			this->maximoX = maximoX;
		}

		PosicionMovil(int coordenadaX, int coordenadaY){
			this->posicionX=coordenadaX;
			this->posicionY=coordenadaY;
			this->minimoY = 2147483647;
			this->minimoX = -2147483648;
			this->maximoX = 2147483647;
		}

		void moverHorizontal(float cantidadAMover){
			if(posicionX + cantidadAMover <= maximoX && posicionX + cantidadAMover >= minimoX)
				this->posicionX+=cantidadAMover;
		}

		void moverHorizontal(int cantidadAMover){
			this->moverHorizontal((float)cantidadAMover);
		}

		void moverVertical(int cantidadAMover){
			if(posicionY + cantidadAMover < minimoY){
				posicionY = minimoY;
			}else{
				this->posicionY+=cantidadAMover;
			}
		}
		void actualizarLimiteTerrenoIzq(int limite){
			minimoX = limite;
		}
		void actualizarLimiteTerrenoDer(int limite){
			maximoX = limite;
		}
		~PosicionMovil(){}
	private:
		int minimoX;
		int maximoX;
};

class PosicionFija : public Posicion{

	public:

		PosicionFija(int coordenadaX,int coordenadaY){
			this->posicionX=coordenadaX;
			this->posicionY=coordenadaY;
		}

};

#endif /* SRC_SERVER_MODELO_POSICION_HPP_ */

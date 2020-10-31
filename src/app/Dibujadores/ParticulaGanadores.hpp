#ifndef SRC_APP_DIBUJADORES_PARTICULAGANADORES_HPP_
#define SRC_APP_DIBUJADORES_PARTICULAGANADORES_HPP_

#include <string>
using namespace std;

class ParticulaGanadores{

	public:
		ParticulaGanadores(int posX,int posY, string imagenAsociada, float factorAvance){
			posicionX = posX;
			posicionY = posY;
			this->imagenAsociada = imagenAsociada;
			this->factorAvance = factorAvance;
		}

		void actualizarPosicion(int altoPantalla){
			if(posicionY > altoPantalla){
				posicionY = 0;
			}
			posicionY += factorAvance;
		}

		 int obtenerX(){
			return posicionX;
		 }
		 int obtenerY(){
			return posicionY;
		 }

		 string particulaAsociada(){
			 return imagenAsociada;
		 }

	private:
		int posicionX;
		int posicionY;
		float factorAvance;
		string imagenAsociada;

};



#endif /* SRC_APP_DIBUJADORES_PARTICULAGANADORES_HPP_ */

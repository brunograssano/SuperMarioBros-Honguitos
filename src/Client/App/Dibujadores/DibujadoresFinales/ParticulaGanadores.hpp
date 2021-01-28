#ifndef SRC_CLIENT_APP_DIBUJADORES_PARTICULAGANADORES_HPP_
#define SRC_CLIENT_APP_DIBUJADORES_PARTICULAGANADORES_HPP_

#include <string>

class ParticulaGanadores{

	public:
		ParticulaGanadores(int posX,int posY, std::string imagenAsociada, float factorAvance);
		void actualizarPosicion(int altoPantalla);
		int obtenerX() const;
		int obtenerY() const;
		std::string particulaAsociada();

	private:
		int posicionX;
		int posicionY;
		float factorAvance;
        std::string imagenAsociada;

};



#endif /* SRC_CLIENT_APP_DIBUJADORES_PARTICULAGANADORES_HPP_ */

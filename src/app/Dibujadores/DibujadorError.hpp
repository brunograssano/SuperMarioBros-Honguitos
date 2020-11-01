#ifndef SRC_APP_DIBUJADORES_DIBUJADORERROR_HPP_
#define SRC_APP_DIBUJADORES_DIBUJADORERROR_HPP_

#include "../CargadorTexturas.hpp"
#include "Dibujador.hpp"

class DibujadorError : public Dibujador{
	public:
		DibujadorError(CargadorTexturas* cargadorTexturas,SDL_Renderer* renderizador, int ancho_pantalla,int alto_pantalla);
		void dibujar();
		~DibujadorError(){};

	private:
		void dibujarError();

};



#endif /* SRC_APP_DIBUJADORES_DIBUJADORERROR_HPP_ */

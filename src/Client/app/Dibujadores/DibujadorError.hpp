#ifndef SRC_CLIENT_APP_DIBUJADORES_DIBUJADORERROR_HPP_
#define SRC_CLIENT_APP_DIBUJADORES_DIBUJADORERROR_HPP_

#include "Dibujador.hpp"
#include "../CargadorTexturas.hpp"

class DibujadorError : public Dibujador{
	public:
		DibujadorError(CargadorTexturas* cargadorTexturas,SDL_Renderer* renderizador, int ancho_pantalla,int alto_pantalla);
		void dibujar();
		~DibujadorError(){};

	private:
		void dibujarError();

};



#endif /* SRC_CLIENT_APP_DIBUJADORES_DIBUJADORERROR_HPP_ */

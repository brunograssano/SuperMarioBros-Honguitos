#ifndef SRC_CLIENT_APP_DIBUJADORES_DIBUJADORERROR_HPP_
#define SRC_CLIENT_APP_DIBUJADORES_DIBUJADORERROR_HPP_

#include "src/Client/app/Dibujadores/Dibujador.hpp"
#include "src/Client/app/CargadorTexturas.hpp"

class DibujadorError : public Dibujador{
	public:
		DibujadorError(CargadorTexturas* cargadorTexturas,SDL_Renderer* renderizador, int ancho_pantalla,int alto_pantalla);
		void dibujar();
		~DibujadorError() override{};

};



#endif /* SRC_CLIENT_APP_DIBUJADORES_DIBUJADORERROR_HPP_ */

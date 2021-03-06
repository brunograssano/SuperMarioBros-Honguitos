#ifndef SRC_CLIENT_APP_DIBUJADORES_DIBUJADORERROR_HPP_
#define SRC_CLIENT_APP_DIBUJADORES_DIBUJADORERROR_HPP_
#include "src/Client/App/CargadorTexturas.hpp"
#include "src/Client/App/Dibujadores/Dibujador.hpp"
#include "src/Client/App/CargadorTexturas.hpp"

class DibujadorError : public Dibujador{
	public:
		DibujadorError(CargadorTexturas* cargadorTexturas,SDL_Renderer* renderizador, int ancho_pantalla,int alto_pantalla);
		void dibujar() override;
		~DibujadorError() override= default;

};



#endif /* SRC_CLIENT_APP_DIBUJADORES_DIBUJADORERROR_HPP_ */

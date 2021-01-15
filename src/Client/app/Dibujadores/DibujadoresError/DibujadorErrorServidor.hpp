#ifndef SRC_CLIENT_APP_DIBUJADORES_DIBUJADORERRORSERVIDOR_HPP_
#define SRC_CLIENT_APP_DIBUJADORES_DIBUJADORERRORSERVIDOR_HPP_

#include "src/Client/app/Dibujadores/Dibujador.hpp"

class DibujadorErrorServidor: public Dibujador{
	public:
		DibujadorErrorServidor(CargadorTexturas* cargadorTexturas,SDL_Renderer* renderizador, int ancho_pantalla,int alto_pantalla);
		void dibujar() override;
		~DibujadorErrorServidor() override;
};

#endif /* SRC_CLIENT_APP_DIBUJADORES_DIBUJADORERRORSERVIDOR_HPP_ */
